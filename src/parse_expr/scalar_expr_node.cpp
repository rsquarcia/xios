#include "scalar_expr_node.hpp"
#include "filter_expr_node.hpp"
#include "type.hpp"
#include "variable.hpp"
#include "operator_expr.hpp"
#include "function.hpp"
#include "context.hpp"
#include "super_filter.hpp"
#include "function.hpp"
#include "filter_graph_types.hpp"

namespace xios
{
  CScalarValExprNode::CScalarValExprNode(const std::string& strVal)
    : strVal(strVal)
  { /* Nothing to do */ }

  SReducedNode CScalarValExprNode::reduce(CContext* context, NodeId parentId) const
  {
    CType<double> val;
    SReducedNode res;
    val.fromString(strVal);
    res.type = SReducedNode::Scalar;
    res.value = val;
    return res;
  }

  CScalarVarExprNode::CScalarVarExprNode(const std::string& varId)
    : varId(varId)
  { /* Nothing to do */ }

  const std::string& CScalarVarExprNode::getVarId() const
  {
    return varId;
  }

  SReducedNode CScalarVarExprNode::reduce(CContext* context, NodeId parentId) const
  {
    SReducedNode res;
    res.type = SReducedNode::Scalar;
    // $missing_value will be replaced with NaN
    if (varId == "missing_value")
    {
      res.value = std::numeric_limits<double>::quiet_NaN();
      return res;
    }
    else
    {
      if (parentId != -1)
      {
        CFilterManager& filterManager = context->getFilterManager();
        std::shared_ptr<CSuperFilter> parentFilter  = filterManager.getSuperFilter(parentId);
        SInputPoint inputPoint = parentFilter->getInputPointFromArgId(varId);
        res.value = inputPoint.node.value;
        return res;
      }
      
      if (!CVariable::has(context, varId)) 
        ERROR("double CScalarVarExprNode::reduce() const", << "The variable " << varId << " does not exist.");
      
      res.value = CVariable::get(context, varId)->getData<double>();
      return res;
    }
  }

  CScalarOpExprNode::CScalarOpExprNode(const std::string& opId, std::initializer_list<IScalarExprNode*> argsList)
    : opId(opId)
  {
    args.assign(argsList.begin(), argsList.end());
  }

   CScalarOpExprNode::CScalarOpExprNode(const std::string& opId, const std::vector<IScalarExprNode*> argsVect)
      : opId(opId)
      , args(argsVect)
    {}

  SReducedNode CScalarOpExprNode::reduce(CContext* context, NodeId parentId) const
  {
    // User-defined function
    SReducedNode res;
    res.type = SReducedNode::Scalar;
    CFunction* fun = nullptr;
    if (CFunction::has(context, opId)) fun = CFunction::get(context, opId);
    
    if (fun)
    {
      //Assume there are no filed in the function expression
      ERROR("double CScalarOpExprNode::reduce() const",
            "Not implemented yet :(");
    }else{
      int argNumber = args.size();

      switch (argNumber)
      {
        case 1: {
          auto op = operatorExpr.getOpScalar(opId);
          res.value =  op((args[0]->reduce(context)).value);
          return res;
        }
        case 2: {
          auto op = operatorExpr.getOpScalarScalar(opId);
          res.value =  op((args[0]->reduce(context)).value, (args[1]->reduce(context)).value);
          return res;
        }
        case 3: {
          auto op = operatorExpr.getOpScalarScalarScalar(opId);
          res.value =  op((args[0]->reduce(context)).value, (args[1]->reduce(context)).value, (args[2]->reduce(context)).value);
          return res;
        }
        default:
          ERROR("double CScalarOpExprNode::reduce() const",
                << "Unsupported number of args for operator " << opId);
      }
    }
  }

}

