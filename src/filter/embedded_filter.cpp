#include "embedded_filter.hpp"
#include "filter_graph_types.hpp"
#include "function.hpp"

namespace xios
{

  extern CLogType logProfile ;

  // Constructor
  // The number of inputPin, outputPin, internalInputPin and internalOutputPin
  // are set at reduce time
  CEmbeddedFilter::CEmbeddedFilter(CGarbageCollector& gc, CFunction& function)
    : CFilter(gc, 1, this)
    , function_(function)
  {
    internalInputPin_ = std::make_shared<CInternalInputPin>(gc, this);
    internalOutputPin_ = std::make_shared<CInternalOutputPin>(gc, false);
    internalOutputPin_->resizeOutputSlots(0);
  }

  // Destructor
  CEmbeddedFilter::~CEmbeddedFilter() = default;

  void CEmbeddedFilter::onInternalPacket(std::vector<CDataPacketPtr> packets)
  {
    this->onOutputReady(packets);
  }

  void CEmbeddedFilter::onInputReady(std::vector<CDataPacketPtr> data)
  {
    std::vector<CDataPacketPtr> outputPacket = engine->apply(data);
    internalOutputPin_->onOutputReady(outputPacket);
  }

  std::vector<CDataPacketPtr> CEmbeddedFilter::apply(std::vector<CDataPacketPtr> data)
  {
    return data;
  }

  void CEmbeddedFilter::connectInternalInputPin(SInputPoint inputPoint, int argoutIdx)
  {
    auto it = slotMap_.find(inputPoint);
    if (it != slotMap_.end())
      connectInternal(argoutIdx, it->second);
    else
      inputPoint.node.outputPin->connectOutput(internalInputPin_, internalSlotsMap_.at(argoutIdx), inputPoint.outIdx); 
  }

  void CEmbeddedFilter::connectInternalOutputPin(std::shared_ptr<CInputPin> inputPin, size_t inputSlot, size_t internalOutputSlot)
  {
    internalOutputPin_->connectOutput(inputPin, inputSlot, internalOutputSlot);
  }

  void CEmbeddedFilter::connectInternal(size_t internalInputSlot, size_t internalOutputSlot)
  {
    internalOutputPin_->connectOutput(internalInputPin_, internalInputSlot, internalOutputSlot);
  }

  void CEmbeddedFilter::trigger(Time timestamp)
  {
    internalInputPin_->trigger(timestamp);
    
    CInputPin::trigger(timestamp);

    COutputPin::trigger(timestamp);
  }

  size_t CEmbeddedFilter::getFunctionArgoutIdx(SArg& arg)
  {
    if (arg.type == SArg::None)       return internalSlotsMap_.at(0);
    if (arg.type == SArg::Positional) return internalSlotsMap_.at(arg.index);
    if (arg.type == SArg::Named)      return internalSlotsMap_.at(function_.getArgoutIdx(arg.name));
    ERROR("size_t CEmbeddedFilter::getFunctionArgoutIdx(SArg& arg)",
          "Undefined arg type : " << arg.type);
    return 0;
  }

  CField* CEmbeddedFilter::getFieldIn(const std::string& arginId)
  {
  if (arginId.empty())
  {
    if (arginMap_.empty())
    ERROR("  CField* CEmbeddedFilter::addExtraInputPoint(const std::string& arginId)",
          " Cannot access any element, the map is empty");
    return arginMap_.begin()->second.node.fieldIn;
  }

  auto it = arginMap_.find(arginId);
  if (it != arginMap_.end())
    return it->second.node.fieldIn;

  ERROR("  CField* CEmbeddedFilter::addExtraInputPoint(const std::string& arginId)",
          " the arginId " << arginId << " does not match any element of the arginMap");
  }

  int CEmbeddedFilter::isFirstOccurence(const SArg& arg)
  {
    size_t idx = function_.getArgoutIdx(arg);
    auto it = internalSlotsMap_.find(idx);

    if (it == internalSlotsMap_.end())
      return idx;

    return -1;
  }

  void CEmbeddedFilter::addInputPoints(std::vector<SInputPoint> inputPoints)
  {
    for (size_t i = 0; i<inputPoints.size(); ++i)
      arginMap_[function_.getArgin()[i]] = inputPoints[i];
  }

  size_t CEmbeddedFilter::getInternalOutputPinSlotNumber()
  {
    return internalOutputPin_->getSlotsCount();
  }

  const SInputPoint CEmbeddedFilter::getInputPointFromArgId(std::string arginId)
  {
    return arginMap_.at(arginId);
  }

  size_t CEmbeddedFilter::getArgSlotIdx(size_t argIdx)
  {
    return slotMap_[getInputPointFromArgId(function_.getArgin()[argIdx])]; 
  }

  SInputPoint CEmbeddedFilter::getInputPointFromSlotIdx(size_t pinIdx)
  {
    for (const auto& entry : slotMap_) 
        if (entry.second == internalSlotsMap_.at(pinIdx))
          return entry.first;
    ERROR("std::string CSuperFilter::getFieldId(size_t pinIdx)",
          "pin is not present in the map");
  }



}