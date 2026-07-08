#include "output_pin.hpp"
#include "exception.hpp"
#include "context.hpp"

#include <vector>

namespace xios
{
  COutputPin::COutputPin(CGarbageCollector& gc, bool manualTrigger /*= false*/)
    : CPin(gc), gc(gc)
    , manualTrigger(manualTrigger), graphEnabled(false)
  {
    resizeOutputSlots(1);
  }

  void COutputPin::connectOutput(std::shared_ptr<CInputPin> inputPin, size_t inputSlot, size_t outputSlot)
  {
    if (!inputPin)
      ERROR("void COutputPin::connectOutput(CInputPin* inputPin, size_t inputSlot)",
            "The input pin cannot be null.");
    
    if (outputSlot>=outputs.size())
      ERROR("void COutputPin::connectOutput(CInputPin* inputPin, size_t inputSlot)",
            "The outputSlot " << outputSlot << " is greater that the output vector size : " << outputs.size());
    outputs[outputSlot].push_back(std::make_pair(inputPin, inputSlot));


    if (canBeTriggered())
      inputPin->setInputTrigger(inputSlot, outputSlot, this);
  }

   void COutputPin::onOutputReady(std::vector<CDataPacketPtr> packets)
  {
    if (!packets[0])
        ERROR("void COutputPin::onOutputReady(std::vector<CDataPacketPtr> packets)",
              "The packets first element cannot be empty.");

    if (manualTrigger)
    {
      auto timestamp = packets[0]->timestamp;
      outputPackets[timestamp] = packets;
      gc.registerObject(this, timestamp); 
    }
    else
    {
      for (size_t i = 0; i < packets.size(); ++i)
      {
        if (packets[i])
          deliverOutput(packets[i], i);
      }
    }
  }

  void COutputPin::deliverOutput(CDataPacketPtr packet, size_t outputSlot = 0)
  {
    if (!packet)
      ERROR("void COutputPin::deliverOutput(CDataPacketPtr packet, size_t outputSlot)",
            "The packet cannot be null.");

    for (const auto& connection : outputs[outputSlot])
    {
      auto inputPin = connection.first;
      auto inputSlot = connection.second;
      inputPin->setInput(inputSlot, packet);
    }
}



  void COutputPin::trigger(Time timestamp)
  {
    if (manualTrigger) // Don't use canBeTriggered here, this function is virtual and can be overriden
    {
      std::map<Time, std::vector<CDataPacketPtr>>::iterator it = outputPackets.find(timestamp);
      if (it != outputPackets.end())
      {
        gc.unregisterObject(this, timestamp);
        for (size_t i = 0; i < it->second.size(); ++i)
          deliverOutput(it->second[i], i);
        outputPackets.erase(it);
      }
    }
  }

  bool COutputPin::canBeTriggered() const
  {
    return manualTrigger;
  }

bool COutputPin::mustAutoTrigger() const
{
    for (auto outerIt = outputs.begin(); outerIt != outputs.end(); ++outerIt)
    {
      for (auto innerIt = outerIt->begin(); innerIt != outerIt->end(); ++innerIt)
      {
        if (innerIt->first && innerIt->first->mustAutoTrigger())
          return true;
      }
    }
    return false;
}


  void COutputPin::setOutputTriggers()
  {
    int i = 0;
    for (auto outerIt = outputs.begin(); outerIt != outputs.end(); ++outerIt)
    {
      for (auto innerIt = outerIt->begin(); innerIt != outerIt->end(); ++innerIt)
      {
        innerIt->first->setInputTrigger(innerIt->second, i, this);
        i++;
      }
    }
  }

  bool COutputPin::isDataExpected(const CDate& date) const
  {
    for (auto outerIt = outputs.begin(); outerIt != outputs.end(); ++outerIt)
    {
      for (auto innerIt = outerIt->begin(); innerIt != outerIt->end(); ++innerIt)
      {
      if (innerIt->first->isDataExpected(date))
        return true;
      }
    }
    return false;
  }

  void COutputPin::invalidate(Time timestamp)
  {
    outputPackets.erase(outputPackets.begin(), outputPackets.lower_bound(timestamp));
  }

  void COutputPin::resizeOutputSlots(size_t newSlotsCount)
  {
  if (!outputPackets.empty())
      ERROR("  void COutputPin::resizeOutputSlots(size_t newSlotsCount)",
          "Cannot resize, some data have been already received!");    
  outputs.resize(newSlotsCount);
  slotsCount = newSlotsCount;
  }

  size_t COutputPin::getSlotsCount()
  {
    return slotsCount;
  }
} // namespace xios
