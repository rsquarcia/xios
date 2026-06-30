#include "filter_expr_node.hpp"
#include "scalar_expr_node.hpp"
#include "unary_arithmetic_filter.hpp"
#include "binary_arithmetic_filter.hpp"
#include "ternary_arithmetic_filter.hpp"
#include "embedded_filter.hpp"
#include "field.hpp"
#include "file.hpp"
#include "function.hpp"
#include "context.hpp"
#include "filter_manager.hpp"
#include "super_filter.hpp"
#include "filter_graph_types.hpp"

namespace xios
{

                  ///////////////////////////
                  // CFilterFieldExprNode ///
                  ///////////////////////////

  CFilterFieldExprNode::CFilterFieldExprNode(const std::string& fieldId)
    : fieldId(fieldId)
  { /* Nothing to do */ }

  SReducedNode CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId) const
  {
    CContext* context = thisField.getContext();
    CFilterManager& filterManager = context->getFilterManager();
    SReducedNode res;
    std::shared_ptr<COutputPin> outputPin;
    SInputPoint inputPoint;
    std::shared_ptr<CSuperFilter> parentFilter;
    inputPoint.outIdx = 0;

    // If superFilter non null and fieldId match an argId, we are on a leaf node of the superFilter's function expr
    // We set the required internal connections
    // We don't set hash there because we need to get the argsubtitution hash
    if (parentId!=-1)
    {
      parentFilter = filterManager.getSuperFilter(parentId);
      std::vector<std::string> argNames = parentFilter->getFunctionArgin();
      if (std::find(argNames.begin(), argNames.end(), fieldId) != argNames.end()) 
      {
        inputPoint = parentFilter->getInputPointFromArgId(fieldId);
        res.outputPin = parentFilter->setInternalConnections(gc, inputPoint); 
        res.fieldIn = inputPoint.node.fieldIn;
        if (inputPoint.node.type == SReducedNode::Field)
        {
          res.type = SReducedNode::Field;
          res.fieldId = inputPoint.node.fieldId;
        }
        else
        {
          res.type = SReducedNode::Filter;
          res.nodeId = inputPoint.node.nodeId;
        }
        return res;
      }
    }
    res.type = SReducedNode::Field;
    res.fieldId = fieldId;
    

    if (fieldId == "this")
    {
      outputPin = thisField.getSelfReference(gc);
      res.fieldId = thisField.getId();
      res.fieldIn = &thisField;
    }
    else
    {
      std::string id;

      if (fieldId == "this_ref")
      {
        if (thisField.field_ref.isEmpty())
        {
          ERROR("std::shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter) const",
                << "field_ref attribute is empty.");
        }
        else id = thisField.field_ref;
      }
      else id = fieldId;
      res.fieldId = id;

      if (CField::has(thisField.getContext(), id))
      {
        CField* field = CField::get(thisField.getContext(), id);
        res.fieldIn = field;
        if (field == &thisField)
          ERROR("std::shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter) const",
                << "The field " << id << " has an invalid reference to itself. "
                << "Use the keyword \"this\" if you want to reference the input data sent to this field.");

        bool ret=field->buildWorkflowGraph(gc);
        if(!field->build_workflow_graph.isEmpty()) thisField.build_workflow_graph.set(field->build_workflow_graph);
        if (ret) outputPin = field->getInstantDataFilter(); // if dependency is complete build the graph other return nullptr  
      }
      else
      {
        ERROR("std::shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter) const",
              << "The field " << id << " does not exist.");
      }
    }
    // If superFilter non null and fieldId doens't match an argId, it corresponds to a fieldId parameter
    //  we are on a leaf node of the EmbeddedFilter's function expr
    res.outputPin = outputPin;
    if (parentFilter)
    {
      inputPoint.node = res;
      parentFilter->setInternalConnections(gc, inputPoint);
    }

    return res;
  }


                      //////////////////////////////////
                      // CFilterTemporalFieldExprNode //
                      //////////////////////////////////


  CFilterTemporalFieldExprNode::CFilterTemporalFieldExprNode(const std::string& fieldId)
    : fieldId(fieldId)
  { /* Nothing to do */ }

  SReducedNode CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId) const
  {
    CContext* context = thisField.getContext();
    CFilterManager& filterManager = context->getFilterManager();
    std::shared_ptr<CFilter> temporalFilter;
    std::shared_ptr<CSuperFilter> parentFilter;
    SReducedNode res;
    SReducedNode input;
    input.type = SReducedNode::Field;
    input.fieldIn = &thisField;
    res.type = SReducedNode::Filter;
    std::string id = fieldId;

    // If superFilter non null and fieldId match an argId, we are on a leaf node of the superFilter's function expr
    // We set the required internal connections
    // We don't set hash there because we need to get the argsubtitution hash
    if (parentId!=-1)
    {
      parentFilter = filterManager.getSuperFilter(parentId);
      std::vector<std::string> argNames = parentFilter->getFunctionArgin();
      if (std::find(argNames.begin(), argNames.end(), id) != argNames.end()) 
      {
        SInputPoint inputPoint = parentFilter->getInputPointFromArgId(id);
        parentFilter->setInternalConnections(gc, inputPoint);
        if (inputPoint.node.type != SReducedNode::Field)
          ERROR("SReducedNode CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId) const",
                "A temporal filter must be aplly on a field !")
        id   =  inputPoint.node.fieldIn->getId();
      }
    }

    if (id == "this")
    {
      CFile* file = thisField.getFileOut();
      temporalFilter = thisField.getSelfTemporalDataFilter(gc, thisField.freq_op.isEmpty() ? TimeStep : thisField.freq_op, !file || file->shouldWriteInitialCondition());
      input.outputPin = thisField.getSelfReference(gc);
    }
    else
    {

      if (id == "this_ref")
      {
        if (thisField.field_ref.isEmpty())
        {
          ERROR("std::shared_ptr<COutputPin> CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter)",
                << "field_ref attribute is empty.");
        }
        else id = thisField.field_ref ;
      }

      if (CField::has(context, id))
      {
        CField* field = CField::get(context, id);
        if (field == &thisField)
          ERROR("std::shared_ptr<COutputPin> CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter)",
                << "The field " << id << " has an invalid reference to itself. "
                << "Use the keyword \"this\" if you want to reference the input data sent to this field.");

        bool ret=field->buildWorkflowGraph(gc);
        if (ret)
        {
          CFile* file = thisField.getFileOut();
          temporalFilter = field->getTemporalDataFilter(gc, thisField.freq_op.isEmpty() ? TimeStep : thisField.freq_op, !file || file->shouldWriteInitialCondition());
          input.outputPin = thisField.getInstantDataFilter();
        }
      }
      else
        ERROR("std::shared_ptr<COutputPin> CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter)",
              << "The field " << id << " does not exist.");
    }
    input.fieldId = id;
    SInputPoint inputPoint{input, 0};
    NodeId nodeId = filterManager.computeOrGetNodeId("@", std::vector<SInputPoint>{inputPoint}, parentId);
    filterManager.addFilter(nodeId, temporalFilter);
    res.outputPin = temporalFilter;
    res.nodeId = nodeId;
    res.fieldIn = input.fieldIn;
    return res;
  }


                        ////////////////////////////
                        //     CFilterOpExprNode  //
                        ////////////////////////////

  CFilterOpExprNode::CFilterOpExprNode(const std::string& opId, std::initializer_list<IExprNode> argsList, const SArg& arg)
    : opId_(opId)
    , arg_(arg)

  {
    args_.assign(argsList.begin(), argsList.end());

  }
  
 CFilterOpExprNode::CFilterOpExprNode(const std::string& opId, const std::vector<IExprNode> argsVect, const SArg& arg)
      : opId_(opId)
      , args_(argsVect)
      , arg_(arg)
  {}
    
  SReducedNode CFilterOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId) const
  {
    CContext* context = thisField.getContext();
    SReducedNode res;
    CFilterManager& filterManager = context->getFilterManager();
    std::shared_ptr<CFilter> filter; 
    std::shared_ptr<CEmbeddedFilter> embeddedFilterBuilder;
    NodeId nodeId;
    CFunction* function = nullptr;
    std::shared_ptr<CSuperFilter> parentFilter;
    
    int key = 0;
    int argsNumber = args_.size();
    res.type = SReducedNode::Filter;
    if (CFunction::has(context, opId_)) function = CFunction::get(context, opId_);
    if (parentId != -1)
      parentFilter = filterManager.getSuperFilter(parentId);


    // Build the bitmask: bit i == 1 means arg i is a Field, 0 means Scalar
    // first bit set to 1 to compare mutliple size combination
    for (size_t i = 0; i < argsNumber; ++i)
      key |= (args_[i].kind << i);
    key |= 1 << argsNumber;

    // We save hashs and reduce results for later connections
    std::vector<SReducedNode> childReductions(argsNumber);
    std::vector<SInputPoint> inputPoints(argsNumber);

    // We call reduce on each child
    for (size_t i = 0; i < argsNumber; ++i)
    {
      size_t argoutIdx = 0;
      SReducedNode reduced;
      if (parentFilter) parentFilter->fillInternalConnectionStack(i);
      if ((key >> i) & 1)  // only for Field
      {
        if (!args_[i].field) { filter.reset(); break; }
        reduced = args_[i].field->reduce(gc, thisField, parentId);
        if (reduced.type == SReducedNode::Filter)
        {
          SArg fieldArg = args_[i].field->getArg();
          argoutIdx = filterManager.getFilterArgoutIdx(reduced.nodeId, fieldArg);
        }
        // We take any childFieldIn (assume they belong to the same grid)
        res.fieldIn = reduced.fieldIn;
      }
      else
      {
        reduced = args_[i].scalar->reduce(thisField.getContext(), parentId);
      }
      SInputPoint inputPoint{reduced, argoutIdx};
      childReductions[i] = reduced;
      inputPoints[i] = inputPoint; 
    }

    nodeId = filterManager.computeOrGetNodeId(opId_, inputPoints, parentId);
    filter = filterManager.getFilter(nodeId);

    // If filter is null, it means that no filter match our current id
    // We need to create a filter
    if (!filter)
    {
      // If the opId match a user defined function id
      if (function)
      {
        if (argsNumber != function->getNumArgin())
        {
          ERROR("  std::shared_ptr<COutputPin> CFilterOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter) const",
                " The number of argin : " << argsNumber << " for the function " << function->getId() << " does not match the number of argin passed in the function : " << function->getNumArgin());
        }         
        // We add all arg hash to the EmbeddedFilter map 
        // Assure their availabilty for the arguemnt during reduce

        embeddedFilterBuilder = std::make_shared<CSuperFilter>(gc, *function);
        filter = embeddedFilterBuilder; 
        nodeId = filterManager.computeOrGetNodeId(opId_, inputPoints, parentId);
        filterManager.addFilter(nodeId, filter);
        embeddedFilterBuilder->addInputPoints(inputPoints);
        int argoutIdx = embeddedFilterBuilder->isFirstOccurence(arg_);
        SInputPoint superSinputPoint = embeddedFilterBuilder->reduceFunction(gc, thisField, nodeId, argoutIdx);
        embeddedFilterBuilder->connectInternalInputPin(superSinputPoint, argoutIdx);
      }
      else
      {
        switch (key)
        {
                            //////////////////
                            // UNARY FILTER //
                            //////////////////

          case 0b11:  // Field
            filter = std::make_shared<CUnaryArithmeticFilter>(gc, opId_);
            break;


                            ///////////////////
                            // BINARY FILTER //
                            ///////////////////

          // Scalar, Field
          case 0b110:
            filter = std::make_shared<CScalarFieldArithmeticFilter>(gc, opId_, childReductions[0].value);
            break;

          // Field, Scalar
          case 0b101:
            filter = std::make_shared<CFieldScalarArithmeticFilter>(gc, opId_, childReductions[1].value);
            break;

          // Field, Field
          case 0b111:
            filter = std::make_shared<CFieldFieldArithmeticFilter>(gc, opId_);
            break;

                              ////////////////////
                              // TERNARY FILTER //
                              ////////////////////

          // Scalar, Scalar, Field 
          case 0b1100:
            filter = std::make_shared<CScalarScalarFieldArithmeticFilter>(
                gc, opId_, childReductions[0].value, childReductions[1].value);
            break;

          // Scalar, Field, Scalar
          case 0b1010:
            filter = std::make_shared<CScalarFieldScalarArithmeticFilter>(
                gc, opId_, childReductions[0].value, childReductions[2].value);
            break;

          // Field, Scalar, Scalar
          case 0b1001:
            filter = std::make_shared<CFieldScalarScalarArithmeticFilter>(
                gc, opId_, childReductions[1].value, childReductions[2].value);
            break;

          // Scalar, Field, Field
          case 0b1110:
            filter = std::make_shared<CScalarFieldFieldArithmeticFilter>(
                gc, opId_, childReductions[0].value);
            break;

          // Field, Scalar, Field
          case 0b1101:
            filter = std::make_shared<CFieldScalarFieldArithmeticFilter>(
                gc, opId_, childReductions[1].value);
            break;

          // Field, Field, Scalar
          case 0b1011:
            filter = std::make_shared<CFieldFieldScalarArithmeticFilter>(
                gc, opId_, childReductions[2].value);
            break;

          // Field, Field, Field
          case 0b1111:
            filter = std::make_shared<CFieldFieldFieldArithmeticFilter>(gc, opId_);
            break;

          default:
            ERROR("  std::shared_ptr<COutputPin> CFilterOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Hash& hash, CField** fieldIn, CEmbeddedFilter* embeddedFilter) const",
                    "Argument combination not supported for built-in XIOS Functions");
        }
        nodeId = filterManager.computeOrGetNodeId(opId_, inputPoints, parentId);
        filterManager.addFilter(nodeId, filter);
      }
      res.nodeId = nodeId;
      // cout << "Currently reducing filter : " << filterManager.toString(nodeId) << " with nodeId : " << nodeId << endl;;

      int k = 0;
     
      // Loop over the child to do the connections
      for (size_t i = 0; i < argsNumber; ++i)
      {
        if ((key >> i) & 1)  // only for Field
        {
          if (embeddedFilterBuilder) break;
          
          // For embeddedFilter and pre-leaf nodes, need special connecting
          if (parentFilter)
          {
            int outIdx = parentFilter->mustBeInternalyConnected(i);
            if (outIdx!=-1) parentFilter->connectInternalOutputPin(filter, k, outIdx);
          }
          else
            childReductions[i].outputPin->connectOutput(filter, k, inputPoints[i].outIdx);
          k = k + 1;
        }
      }
      if (parentFilter) parentFilter->popInternalConnections();

    }
    else
    {
      if (auto embeddedFilter = std::dynamic_pointer_cast<CEmbeddedFilter>(filter)) 
      {
        if (args_.size() == 0) res.fieldIn = embeddedFilter->getFieldIn();
        int idxIsFirst = embeddedFilter->isFirstOccurence(arg_);
        if (idxIsFirst != -1)
        {
          SInputPoint inputPoint = embeddedFilter->reduceFunction(gc, thisField, nodeId, idxIsFirst);
          embeddedFilter->connectInternalInputPin(inputPoint, idxIsFirst);
        }
      }
    }

    const bool buildGraph_ = !(thisField.build_workflow_graph.isEmpty()) &&
                              thisField.build_workflow_graph == true;
    if (buildGraph_)
    {
      filter->graphPackage = new CGraphPackage;
      filter->graphEnabled = true;
      filter->graphPackage->inFields.push_back(&thisField);
    }
    
    res.outputPin = filter;
    return res;
  }

}
