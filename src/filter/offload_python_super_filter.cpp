#include "offload_python_super_filter.hpp"
#include "python_filter.hpp"
#include "timer.hpp"
#include "function.hpp"
#include "field.hpp"
#include "filter_manager.hpp"
#include "grid.hpp"
#include "exception.hpp"
#include "calendar_util.hpp"
#include "context.hpp"
#include "event_client.hpp"
#include "tracer.hpp"
#include "field.hpp"
#include<vector>


namespace xios
{

  extern CLogType logProfile ;

  // Constructor
  COffloadPythonSuperFilter::COffloadPythonSuperFilter(CGarbageCollector& gc, CFunction& function)
    : CEmbeddedFilter(gc, function)
  {}

  // Destructor
  COffloadPythonSuperFilter::~COffloadPythonSuperFilter() = default;


  void COffloadPythonSuperFilter::createInternalFieldOut(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx, size_t internalIdx)
  {
    const StdString& internalFieldOutId = fieldOut.getId()+"__offload_argout__"+std::to_string(nodeId)+std::to_string(argoutIdx);
    CField* internalFieldOut = CField::create(getContext(), internalFieldOutId);
    internalFieldOut->read_access.setValue(true);
    internalFieldOut->setGrid(fieldOut.getGrid());
    internalFieldOut->setOffloadFunction(&function_);
    function_.addOffloadFieldOut(internalFieldOut);
  
    std::string newExpression = function_.getId() + "(";
    bool first = true;
    for (const CFunction::SArgIn& arg : function_.getArgs(nodeId))
    {
      if (!first) newExpression += ",";
      if (arg.isVariable())
        newExpression += "$";
      newExpression += arg.getId();
      first = false;  
    }

    newExpression += ")";

    internalFieldOut->setOffloadExpression(newExpression+"["+std::to_string(argoutIdx)+"]");
  
    internalFieldOut->connectOutEmbededFilter(gc, internalInputPin_, internalIdx);
    internalFieldOut->setPythonSuperFilter(shared_from_this());
  }




  SInputPoint COffloadPythonSuperFilter::reduceFunction(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx) 
  {
    size_t internalIdx = internalSlotsMap_.size();
    resizeOutputSlots(internalIdx+1);
    internalInputPin_->resizeInputSlots(internalIdx+1);
    internalSlotsMap_[argoutIdx] = internalIdx;
    SReducedNode reduced;
    reduced.type = SReducedNode::Filter;
    reduced.nodeId = nodeId;
    size_t k = 0;

    for (size_t i = 0; i<function_.getNumArgin(); ++i)
    {
      SInputPoint inputPoint = arginMap_[function_.getArgin()[i]];
      if (inputPoint.node.type == SReducedNode::Scalar)
      {
        CVariable* scalar = CVariable::create(getContext(), "scalar__offload_argin__"+std::to_string(nodeId)+std::to_string(i));
        scalar->setData<double>(inputPoint.node.value);
        scalar->setOffloadFunction(&function_);
        function_.addFilterArgin(nodeId, scalar, i);
      }
      else
      {
        internalOutputPin_->resizeOutputSlots(k+1);
        resizeInputSlots(k+1);

        CField* fieldIn = inputPoint.node.fieldIn;
        const StdString& internalFieldInId = fieldIn->getId()+"__offload_argin__"+std::to_string(nodeId)+std::to_string(i);
        CField* internalFieldIn = CField::create(getContext(),internalFieldInId);
        internalFieldIn->solveRefInheritance();
        internalFieldIn->setGrid(fieldIn->getGrid());
        internalFieldIn->grid_ref = fieldIn->getGrid()->getId();

        internalFieldIn->connectInEmbededFilter(gc, internalOutputPin_, k);
        internalFieldIn->setPythonSuperFilter(shared_from_this());
        internalFieldIn->setOffloadFunction(&function_);
        function_.addFilterArgin(nodeId, internalFieldIn, i);
        inputPoint.node.outputPin->connectOutput(shared_from_this(), k, inputPoint.outIdx);
        ++k;
      }
    }
    createInternalFieldOut(gc, fieldOut, nodeId, argoutIdx, internalIdx);
    SInputPoint pythonPoint{reduced, argoutIdx};

    return pythonPoint;
  }

  // The internal connections are done by createInternalFieldOut
  void COffloadPythonSuperFilter::connectInternalInputPin(SInputPoint inputPoint, int argoutIdx)
  {
    return ;
  }

  std::vector<CDataPacketPtr> COffloadPythonSuperFilter::apply(std::vector<CDataPacketPtr> data)
  {
    isExpectingOffloadedData_ = true;
    expectDataAtTimeStep_ = data[0]->timestamp;
    return data;
  }

  bool COffloadPythonSuperFilter::isExpectingOffloadData()
  {
    return isExpectingOffloadedData_;
  }

  Time COffloadPythonSuperFilter::getExpectDataAtTimeStep()
  {
    return expectDataAtTimeStep_;
  }

  void COffloadPythonSuperFilter::receivedOffloadedData()
  {
    nbReceivedOffloadedData_++;
  }

  void COffloadPythonSuperFilter::checkForLateData(void)
  TRY
  {
    CContext* context = getContext();

    if (isExpectingOffloadedData_ && expectDataAtTimeStep_ == Time(context->getCalendar()->getCurrentDate()))
    {
      CTimer timer("COffloadPythonSuperFilter::checkForLateData");
      timer.resume();
      traceOff() ;
      timer.suspend();
      while (nbReceivedOffloadedData_ != COutputPin::getSlotsCount())
      {
        timer.resume();
        context->globalEventLoop();
        context->eventLoop() ; 
        timer.suspend();
      }
      nbReceivedOffloadedData_ = 0 ;
      timer.resume();
      traceOn() ;
      timer.suspend() ;
      isExpectingOffloadedData_ = false;
      trigger(expectDataAtTimeStep_);
    }
    
  }
  CATCH

}