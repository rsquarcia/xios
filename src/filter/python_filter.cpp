#include "python_filter.hpp"
#include "garbage_collector.hpp"
#include "function.hpp"
#include "python_manager.hpp"
#include "embedded_filter.hpp"
#include "attribute_template.hpp"
#include "context.hpp"
#include "variable.hpp"

namespace xios
{

  CPythonFilter::CPythonFilter(CGarbageCollector& gc, CFunction& function, NodeId superFilterId)
    : CFilter(gc, 1, this)
    , function_(function)
    , isInitialized_(false)
    , pyFilterIdx_(-1)
    , superFilterId_(superFilterId)
    {
      resizeOutputSlots(function_.getNumArgout());
      resizeInputSlots(1);
    }

  CPythonFilter::~CPythonFilter() = default;



  std::vector<CDataPacketPtr> CPythonFilter::apply(std::vector<CDataPacketPtr> data)
  {
    auto& pythonManager = CPythonManager::instance();
    std::vector<CDataPacketPtr> packets;

    if (!isInitialized_)
    {
      pythonManager.initialize();
      pyFilterIdx_ = pythonManager.initializePythonFilter(function_, superFilterId_, getContext()->getId());
      isInitialized_ = true;
    }
    packets = pythonManager.applyPythonFilter(data, function_, pyFilterIdx_);
    return packets;
  }

}
