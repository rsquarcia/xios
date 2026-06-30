#include "input_pin.hpp"
#include "output_pin.hpp"
#include "garbage_collector.hpp"
#include "exception.hpp"

namespace xios
{
  CInputPin::CInputPin(CGarbageCollector& gc, size_t slotsCount)
    : CPin(gc), gc(gc)
    , slotsCount(slotsCount)
    , triggers(slotsCount)
    , hasTriggers(false)
  { /* Nothing to do */ }

  void CInputPin::setInput(size_t inputSlot, CDataPacketPtr packet)
  {
    if (inputSlot >= slotsCount)
      ERROR("void CInputPin::setInput(size_t inputSlot, CDataPacketPtr packet)",
            "The input slot " << inputSlot << " does not exist.");
    if (!packet)
      ERROR("void CInputPin::setInput(size_t inputSlot, CDataPacketPtr packet)",
            "The packet cannot be null.");

    std::map<Time, InputBuffer>::iterator it = inputs.find(packet->timestamp);
    if (it == inputs.end())
    {
      it = inputs.insert(std::make_pair(packet->timestamp, InputBuffer(slotsCount))).first;
      gc.registerObject(this, packet->timestamp);
    }
    if (it->second.packets[inputSlot])
        ERROR("void CInputPin::setInput(size_t inputSlot, CDataPacketPtr packet)",
              "The inputSlot " << inputSlot << " has already been filled ! ")

    it->second.slotsFilled++;
    it->second.packets[inputSlot] = packet;

    if (it->second.slotsFilled == slotsCount)
    {
      // Unregister before calling onInputReady in case the filter registers again
      gc.unregisterObject(this, packet->timestamp);
      onInputReady(it->second.packets);
      inputs.erase(it);
    }
  }

  void CInputPin::setInputTrigger(size_t inputSlot, size_t outputSlot, COutputPin* trigger)
  {
    if (inputSlot >= slotsCount)
      ERROR("void CInputPin::setInputTrigger(size_t inputSlot, COutputPin* trigger)",
            "The input slot " << inputSlot << " does not exist.");
    if (triggers[inputSlot].first && triggers[inputSlot].second == outputSlot)
      ERROR("void CInputPin::setInputTrigger(size_t inputSlot, COutputPin* trigger)",
            "The trigger for input slot <-> output slot : " << inputSlot << " <-> " << outputSlot << " has already been set.");

    triggers[inputSlot] = std::make_pair(trigger, outputSlot);
    hasTriggers = true;
  }

  void CInputPin::trigger(Time timestamp)
  {
    if (hasTriggers) // Don't use canBeTriggered here, this function is virtual and can be overriden
    {
      std::map<Time, InputBuffer>::iterator it = inputs.find(timestamp);
      bool nothingReceived = (it == inputs.end());

      for (size_t s = 0; s < slotsCount; s++)
      {
        if (triggers[s].first && (nothingReceived || !it->second.packets[s]))
          triggers[s].first->trigger(timestamp);
      }
    }
  }

  bool CInputPin::canBeTriggered() const
  {
    return hasTriggers;
  }

  void CInputPin::invalidate(Time timestamp)
  {
    inputs.erase(inputs.begin(), inputs.lower_bound(timestamp));
  }

  void CInputPin::resizeInputSlots(size_t newSlotsCount)
  {
  if (!inputs.empty())
      ERROR("  void CInputPin::resizeSlots(size_t newSlotsCount)",
          "Cannot resize, some data have been already received!");    
  triggers.resize(newSlotsCount); // The slot is set after
  slotsCount = newSlotsCount;
  }

} // namespace xios
