#ifndef __XIOS_TRANSFORMATION_BASE__
#define __XIOS_TRANSFORMATION_BASE__

#include "transformation_enum.hpp"

namespace xios
{
  class CTransformationBase
  {
    public:
      virtual ETranformationType getTransformationType(void)=0; 
  } ;
}

#endif