#ifndef __XIOS_OBJECT_TEMPLATE_IMPL_HPP__
#define __XIOS_OBJECT_TEMPLATE_IMPL_HPP__

#include "object_transform_template.hpp"

#include "field.hpp"
#include "context.hpp"

namespace xios
{
  template <class T>
  CObjectTransformTemplate<T>::CObjectTransformTemplate(CContext* context) : CObjectTemplate<T>(context)
  { /* Ne rien faire de plus */ }

  template <class T>
  CObjectTransformTemplate<T>::CObjectTransformTemplate(CContext* context, const StdString & id)
    : CObjectTemplate<T>(context, id)
  { /* Ne rien faire de plus */ }

  template <class T>
  CObjectTransformTemplate<T>::~CObjectTransformTemplate(void)
  { /* Ne rien faire de plus */ }

  
  template <typename T>
  T* CObjectTransformTemplate<T>::get(CContext* context, const string& id, bool noError)
  {

    const regex r("::");
    smatch m;
    if (regex_search(id, m, r))
    {
      if (m.size()!=1) ERROR("T* CObjectTemplate<T>::getForTransform(CContext* context, const string& id)", <<" id = "<<id<< "  -> bad format id, separator :: append more than one time");
      string fieldId=m.prefix() ;
      if (fieldId.empty()) ERROR("T* CObjectTemplate<T>::getForTransform(CContext* context, const string& id)", <<" id = "<<id<< "  -> bad format id, field name is empty");
      string suffix=m.suffix() ;
      if (!CField::has(context, fieldId)) 
      {
        if (noError)  return nullptr ;
        else ERROR("T* CObjectTemplate<T>::getForTransform(CContext* context, const string& id)", <<" id = "<<id<< "  -> field Id : < "<<fieldId<<" > doesn't exist");
      }
        CField* field=CField::get(context, fieldId) ;
        return dynamic_cast<T*>(field->getAppliedTransformation(T::getTransType())) ;
    }
    {
      if (noError) if(!CObjectFactory::HasObject<T>(context->getId(), id)) return nullptr ;
      return CObjectFactory::GetObject<T>(context->getId(), id).get();
    }
  }

  template <typename T>
  bool CObjectTransformTemplate<T>::has(CContext* context, const string& id)
  {
    if (CObjectTransformTemplate<T>::get(context, id, true)==nullptr) return false ;
    else return true ;
  }

}
#endif