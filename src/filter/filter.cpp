#include "filter.hpp"
#include "timer.hpp"

#include <vector>

namespace xios
{
  extern CLogType logProfile ;
  CFilter::CFilter(CGarbageCollector& gc, size_t inputSlotsCount, IFilterEngine* engine)
    : CInputPin(gc, inputSlotsCount)
    , COutputPin(gc)
    , engine(engine)
    , inputSlotCount(inputSlotsCount)
  { /* Nothing to do */ }

  void CFilter::onInputReady(std::vector<CDataPacketPtr> data)
  {
    if (info.isActive(logProfile)) CTimer::get("Applying filters").resume() ;
    std::vector<CDataPacketPtr> outputPacket = engine->apply(data);
    if (info.isActive(logProfile)) CTimer::get("Applying filters").suspend() ;
    if (!outputPacket.empty())
      onOutputReady(outputPacket);
  }

  void CFilter::setInputTrigger(size_t inputSlot, size_t outputSlot, COutputPin* trigger)
  {
    // Was the filter already triggerable? If not, we need to inform
    // all downstream filters.
    bool wasTriggerable = canBeTriggered();

    CInputPin::setInputTrigger(inputSlot, outputSlot, trigger);

    if (!wasTriggerable)
      setOutputTriggers();
  }

  void CFilter::trigger(Time timestamp)
  {
    CInputPin::trigger(timestamp);

    COutputPin::trigger(timestamp);
  }

  bool CFilter::canBeTriggered() const
  {
    return (CInputPin::canBeTriggered() || COutputPin::canBeTriggered());
  }

  bool CFilter::mustAutoTrigger() const
  {
    return COutputPin::mustAutoTrigger();
  }

  bool CFilter::isDataExpected(const CDate& date) const
  {
    return COutputPin::isDataExpected(date);
  }
} // namespace xios
