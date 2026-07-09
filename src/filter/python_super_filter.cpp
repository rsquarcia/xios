#include "python_super_filter.hpp"
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
#include<algorithm>


namespace xios
{

  extern CLogType logProfile ;

  // Constructor
  CPythonSuperFilter::CPythonSuperFilter(CGarbageCollector& gc, CFunction& function)
    : CEmbeddedFilter(gc, function)
  {}

  // Destructor
  CPythonSuperFilter::~CPythonSuperFilter() = default;


  SInputPoint CPythonSuperFilter::reduceFunction(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx)
  {
    pythonFilter_ = std::make_shared<CPythonFilter>(gc, function_, nodeId);
    size_t internalIdx = internalSlotsMap_.size();
    resizeOutputSlots(internalIdx+1);
    internalInputPin_->resizeInputSlots(internalIdx+1);
    internalSlotsMap_[argoutIdx] = internalIdx;
    SReducedNode reduced;
    reduced.type = SReducedNode::Filter;
    reduced.nodeId = nodeId;
    reduced.outputPin = pythonFilter_;
    size_t k = 0;

    for (size_t i = 0; i<function_.getNumArgin(); ++i)
    {
      SInputPoint inputPoint = arginMap_[function_.getArgin()[i]];
      if (inputPoint.node.type == SReducedNode::Scalar)
      {
        CVariable* scalar = CVariable::create(getContext(), "scalar_argin__"+std::to_string(nodeId)+std::to_string(i));
        scalar->setData<double>(inputPoint.node.value);
        function_.addFilterArgin(nodeId, scalar, i);
      }
      else
      {
        function_.addFilterArgin(nodeId, inputPoint.node.fieldIn, i);
        internalOutputPin_->resizeOutputSlots(k+1);
        resizeInputSlots(k+1);
        pythonFilter_->resizeInputSlots(k+1);
        internalOutputPin_->connectOutput(pythonFilter_, k, k);
        inputPoint.node.outputPin->connectOutput(shared_from_this(), k, inputPoint.outIdx);
        ++k;
      }
    }

    SInputPoint pythonPoint{reduced, argoutIdx};

    return pythonPoint;
  }


  std::vector<CDataPacketPtr> CPythonSuperFilter::apply(std::vector<CDataPacketPtr> data)
  {
    return data;
  }

}