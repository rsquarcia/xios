#ifndef __XIOS_CInternalInputPin__
#define __XIOS_CInternalInputPin__

#include "input_pin.hpp"

namespace xios
{
  class CEmbeddedFilter;

  class CInternalInputPin : public CInputPin
  {
    public:
      CInternalInputPin(CGarbageCollector& gc, CEmbeddedFilter* parentFilter);
      bool mustAutoTrigger() const;
      bool isDataExpected(const CDate& date) const;
      void virtual setInputTrigger(size_t inputSlot, size_t outputSlot, COutputPin* trigger) override;
    
      private:
        CEmbeddedFilter* parentFilter;
        void onInputReady(std::vector<CDataPacketPtr> data) override;

  }; 
} // namespace xios

#endif //__XIOS_CInternalInputPin__
