#include "internal_input_pin.hpp"
#include "embedded_filter.hpp"


namespace xios{
  CInternalInputPin::CInternalInputPin(CGarbageCollector& gc, CEmbeddedFilter* parentFilter)
      : CInputPin(gc, 1)
      , parentFilter(parentFilter)
    { /* Nothing to do */ }

      bool CInternalInputPin::mustAutoTrigger() const
      {
        return true;
      }

      bool CInternalInputPin::isDataExpected(const CDate& date) const
      {
        return true;
      }

      void CInternalInputPin::onInputReady(std::vector<CDataPacketPtr> data)
      {
        parentFilter->onInternalPacket(data);
      }

      void CInternalInputPin::setInputTrigger(size_t inputSlot, size_t outputSlot, COutputPin* trigger)
      {
        CInputPin::setInputTrigger(inputSlot, outputSlot, trigger);
        if (inputSlot == 0 && !parentFilter->canBeTriggered()) parentFilter->setOutputTriggers();
      }

}