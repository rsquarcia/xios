#include "super_filter.hpp"
#include "timer.hpp"
#include "function.hpp"
#include "field.hpp"
#include "filter_manager.hpp"
#include "filter_expr_node.hpp"
#include "context.hpp"

#include<vector>


namespace xios
{

  extern CLogType logProfile ;

  // Constructor
  CSuperFilter::CSuperFilter(CGarbageCollector& gc, CFunction& function)
    : CEmbeddedFilter(gc, function)
  {}

  // Destructor
  CSuperFilter::~CSuperFilter() = default;

  // Reduce the vector of call tree from function_ into a vector of (outputPin, outputIdx) where outputIdx is the outputPin slot idx 
  // corresponding to the required output
  SInputPoint CSuperFilter::reduceFunction(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx)
  {
    CFilterManager& filterManager = getContext()->getFilterManager();
    size_t internalIdx = internalSlotsMap_.size();
    std::shared_ptr<IFilterExprNode> expr(function_.getTreeFromExpr()[argoutIdx]);
    // We get the vector of expression (multiple output expression), lazy parsing
    if (argoutIdx >= function_.getNumArgout() || argoutIdx == -1)
       ERROR("SInputPoint CSuperFilter::reduceFunction(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx)",
            " The argoutIdx " << argoutIdx << " is out of bound ! There are only " << function_.getNumArgout() << " outputs available for the function " << function_.getId());

    // We update the embeddedFilter pinSlot numbers
    resizeOutputSlots(internalIdx+1);
    internalInputPin_->resizeInputSlots(internalIdx+1);
    internalSlotsMap_[argoutIdx] = internalIdx;

    size_t childArgoutIdx = 0;
    SReducedNode reduced = expr->reduce(gc, fieldOut, nodeId);
    if (reduced.type == SReducedNode::Filter)
    {
      SArg childArg = expr->getArg();
      childArgoutIdx = filterManager.getFilterArgoutIdx(reduced.nodeId, childArg);
    }
    
    SInputPoint inputPoint{reduced, childArgoutIdx};

    return inputPoint; 
  }


  // true if we need to do a connection to an internalOutputPin
  int CSuperFilter::mustBeInternalyConnected(size_t slotIdx)
  {
    if (internalConnection_.empty()) return -1;
    if (internalConnection_.top()[slotIdx] == -1) return -1;
    return internalConnection_.top()[slotIdx];
  }

  // Fill the internalConnection_ stack along the reduce recursion to keep track of the recursion tree
  void CSuperFilter::fillInternalConnectionStack(size_t idx)
  {
    if (internalConnection_.empty())
      internalConnection_.push({-1});
    else
    {
      std::vector<int>& top = internalConnection_.top();
      if (idx == top.size())
        top.push_back(-1);
      else
        internalConnection_.push({-1});
    }
  }

  void CSuperFilter::popInternalConnections()
  {
    if (!internalConnection_.empty()) internalConnection_.pop();
  }


  // Called at leaf level in the reduce, allow to proceed internalConnection
  const std::shared_ptr<CInternalOutputPin> CSuperFilter::setInternalConnections(CGarbageCollector& gc, SInputPoint inputPoint)
  {
    auto it = slotMap_.find(inputPoint);
    size_t idx;

    // The internalOutputPin associated to id already exist
    if (it != slotMap_.end()) {
      idx = it->second;
      if (!internalConnection_.empty()) internalConnection_.top().back() = idx;
      return internalOutputPin_;
    } 

    // we need to create a new slot
    idx = internalOutputPin_->getSlotsCount();
    slotMap_[inputPoint] = idx;  

    internalOutputPin_->resizeOutputSlots(idx + 1);
    resizeInputSlots(idx + 1);

    if (!internalConnection_.empty()) internalConnection_.top().back() = idx;
    inputPoint.node.outputPin -> connectOutput(shared_from_this(), idx, inputPoint.outIdx);
    return internalOutputPin_;
  }


  const std::vector<std::string> CSuperFilter::getFunctionArgin()
  {
    return function_.getArgin();
  }

}