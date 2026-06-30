#include "internal_output_pin.hpp"

namespace xios{
  CInternalOutputPin::CInternalOutputPin(CGarbageCollector& gc, bool manualTrigger)
      : COutputPin(gc, manualTrigger)
    { /* Nothing to do */ }

}