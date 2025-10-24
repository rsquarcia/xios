#ifndef __XIOS_OBJECT_TRANSFORM_TEMPLATE_HPP__
#define __XIOS_OBJECT_TRANSFORM_TEMPLATE_HPP__

#include "object_template.hpp"

namespace xios
{
   /// ////////////////////// Déclarations ////////////////////// ///
   class CContext ;

   template <class T>
   class CObjectTransformTemplate : public CObjectTemplate<T>
   {
      public :
      /// Constructeurs ///
      CObjectTransformTemplate(CContext* context);
      explicit CObjectTransformTemplate(CContext* context, const StdString& id);

      /// Destructeur ///
      virtual ~CObjectTransformTemplate(void);

      static T* get(CContext* context, const string& id, bool noError=false);
      static bool has(CContext* context, const string& id) ;
      static T* get(CContext* context, const T* ptr) { return CObjectTemplate<T>::get(context,ptr); } 
    };
}

#endif
