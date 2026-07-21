/* ************************************************************************** *
 *               Interface auto generated - do not modify                     *
 * ************************************************************************** */

#include "xios.hpp"
#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "icutil.hpp"
#include "icdate.hpp"
#include "timer.hpp"
#include "node_type.hpp"

extern "C"
{
  typedef xios::CFunction* function_Ptr;

  void cxios_set_function_argin(function_Ptr function_hdl, const char * argin, int argin_size)
  {
    std::string argin_str;
    if (!cstr2string(argin, argin_size, argin_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->argin.setValue(argin_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_argin(function_Ptr function_hdl, char * argin, int argin_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->argin.getInheritedValue(), argin, argin_size))
      ERROR("void cxios_get_function_argin(function_Ptr function_hdl, char * argin, int argin_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_argin(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->argin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_argout(function_Ptr function_hdl, const char * argout, int argout_size)
  {
    std::string argout_str;
    if (!cstr2string(argout, argout_size, argout_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->argout.setValue(argout_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_argout(function_Ptr function_hdl, char * argout, int argout_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->argout.getInheritedValue(), argout, argout_size))
      ERROR("void cxios_get_function_argout(function_Ptr function_hdl, char * argout, int argout_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_argout(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->argout.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_comment(function_Ptr function_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_comment(function_Ptr function_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_function_comment(function_Ptr function_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_comment(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_expr(function_Ptr function_hdl, const char * expr, int expr_size)
  {
    std::string expr_str;
    if (!cstr2string(expr, expr_size, expr_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->expr.setValue(expr_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_expr(function_Ptr function_hdl, char * expr, int expr_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->expr.getInheritedValue(), expr, expr_size))
      ERROR("void cxios_get_function_expr(function_Ptr function_hdl, char * expr, int expr_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_expr(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->expr.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_long_name(function_Ptr function_hdl, const char * long_name, int long_name_size)
  {
    std::string long_name_str;
    if (!cstr2string(long_name, long_name_size, long_name_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->long_name.setValue(long_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_long_name(function_Ptr function_hdl, char * long_name, int long_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->long_name.getInheritedValue(), long_name, long_name_size))
      ERROR("void cxios_get_function_long_name(function_Ptr function_hdl, char * long_name, int long_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_long_name(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->long_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_name(function_Ptr function_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_name(function_Ptr function_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_function_name(function_Ptr function_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_name(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_offload(function_Ptr function_hdl, const char * offload, int offload_size)
  {
    std::string offload_str;
    if (!cstr2string(offload, offload_size, offload_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->offload.setValue(offload_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_offload(function_Ptr function_hdl, char * offload, int offload_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->offload.getInheritedValue(), offload, offload_size))
      ERROR("void cxios_get_function_offload(function_Ptr function_hdl, char * offload, int offload_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_offload(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->offload.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_offset(function_Ptr function_hdl, cxios_duration offset_c)
  {
    CTimer::get("XIOS").resume();
    function_hdl->offset.allocate();
    CDuration& offset = function_hdl->offset.get();
    offset.year = offset_c.year;
    offset.month = offset_c.month;
    offset.day = offset_c.day;
    offset.hour = offset_c.hour;
    offset.minute = offset_c.minute;
    offset.second = offset_c.second;
    offset.timestep = offset_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_offset(function_Ptr function_hdl, cxios_duration* offset_c)
  {
    CTimer::get("XIOS").resume();
    CDuration offset = function_hdl->offset.getInheritedValue();
    offset_c->year = offset.year;
    offset_c->month = offset.month;
    offset_c->day = offset.day;
    offset_c->hour = offset.hour;
    offset_c->minute = offset.minute;
    offset_c->second = offset.second;
    offset_c->timestep = offset.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_offset(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_pool_offload(function_Ptr function_hdl, const char * pool_offload, int pool_offload_size)
  {
    std::string pool_offload_str;
    if (!cstr2string(pool_offload, pool_offload_size, pool_offload_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->pool_offload.setValue(pool_offload_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_pool_offload(function_Ptr function_hdl, char * pool_offload, int pool_offload_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->pool_offload.getInheritedValue(), pool_offload, pool_offload_size))
      ERROR("void cxios_get_function_pool_offload(function_Ptr function_hdl, char * pool_offload, int pool_offload_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_pool_offload(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->pool_offload.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_pysrc(function_Ptr function_hdl, const char * pysrc, int pysrc_size)
  {
    std::string pysrc_str;
    if (!cstr2string(pysrc, pysrc_size, pysrc_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->pysrc.setValue(pysrc_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_pysrc(function_Ptr function_hdl, char * pysrc, int pysrc_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->pysrc.getInheritedValue(), pysrc, pysrc_size))
      ERROR("void cxios_get_function_pysrc(function_Ptr function_hdl, char * pysrc, int pysrc_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_pysrc(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->pysrc.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_function_standard_name(function_Ptr function_hdl, const char * standard_name, int standard_name_size)
  {
    std::string standard_name_str;
    if (!cstr2string(standard_name, standard_name_size, standard_name_str)) return;
    CTimer::get("XIOS").resume();
    function_hdl->standard_name.setValue(standard_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_function_standard_name(function_Ptr function_hdl, char * standard_name, int standard_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(function_hdl->standard_name.getInheritedValue(), standard_name, standard_name_size))
      ERROR("void cxios_get_function_standard_name(function_Ptr function_hdl, char * standard_name, int standard_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_function_standard_name(function_Ptr function_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = function_hdl->standard_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
