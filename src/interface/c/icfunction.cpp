/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */


#include <memory>

#include "xios.hpp"

#include "object_template.hpp"
#include "group_template.hpp"
#include "attribute_template.hpp"

#include "icutil.hpp"
#include "timer.hpp"
#include "function.hpp"
#include "context.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------
   
   typedef xios::CFunction      * XFunctionPtr;
   typedef xios::CFunctionGroup * XFunctionGroupPtr;

   // ------------------------ Création des handle -----------------------------
   
   void cxios_function_handle_create (XFunctionPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id; 
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CFunction::get(CContext::getCurrent(), id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK
   
   void cxios_functiongroup_handle_create (XFunctionGroupPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id; 
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CFunctionGroup::get(CContext::getCurrent(), id);
      CTimer::get("XIOS").suspend() ;
    }
   CATCH_DUMP_STACK

   // -------------------- Vérification des identifiants -----------------------

   void cxios_function_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CFunction::has(CContext::getCurrent(), id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   void cxios_functiongroup_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CFunctionGroup::has(CContext::getCurrent(), id);
      CTimer::get("XIOS").suspend() ;

   }
   CATCH_DUMP_STACK
   
} // extern "C"
