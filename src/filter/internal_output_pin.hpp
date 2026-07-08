#ifndef __XIOS_CInternalOutputPin__
#define __XIOS_CInternalOutputPin__

#include "output_pin.hpp"

namespace xios
{
  class CInternalOutputPin : public COutputPin
  {
    public:
      friend class CEmbeddedFilter;
      using COutputPin::resizeOutputSlots;
      CInternalOutputPin(CGarbageCollector& gc, bool manualTrigger);


 
  }; 
} // namespace xios

#endif //__XIOS_CInternalOutputPin__
