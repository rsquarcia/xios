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
  typedef xios::CFunctionGroup* functiongroup_Ptr;

  void cxios_set_functiongroup_argin(functiongroup_Ptr functiongroup_hdl, const char * argin, int argin_size)
  {
    std::string argin_str;
    if (!cstr2string(argin, argin_size, argin_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->argin.setValue(argin_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_argin(functiongroup_Ptr functiongroup_hdl, char * argin, int argin_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->argin.getInheritedValue(), argin, argin_size))
      ERROR("void cxios_get_functiongroup_argin(functiongroup_Ptr functiongroup_hdl, char * argin, int argin_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_argin(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->argin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_argout(functiongroup_Ptr functiongroup_hdl, const char * argout, int argout_size)
  {
    std::string argout_str;
    if (!cstr2string(argout, argout_size, argout_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->argout.setValue(argout_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_argout(functiongroup_Ptr functiongroup_hdl, char * argout, int argout_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->argout.getInheritedValue(), argout, argout_size))
      ERROR("void cxios_get_functiongroup_argout(functiongroup_Ptr functiongroup_hdl, char * argout, int argout_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_argout(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->argout.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_comment(functiongroup_Ptr functiongroup_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_comment(functiongroup_Ptr functiongroup_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_functiongroup_comment(functiongroup_Ptr functiongroup_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_comment(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_expr(functiongroup_Ptr functiongroup_hdl, const char * expr, int expr_size)
  {
    std::string expr_str;
    if (!cstr2string(expr, expr_size, expr_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->expr.setValue(expr_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_expr(functiongroup_Ptr functiongroup_hdl, char * expr, int expr_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->expr.getInheritedValue(), expr, expr_size))
      ERROR("void cxios_get_functiongroup_expr(functiongroup_Ptr functiongroup_hdl, char * expr, int expr_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_expr(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->expr.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_group_ref(functiongroup_Ptr functiongroup_hdl, const char * group_ref, int group_ref_size)
  {
    std::string group_ref_str;
    if (!cstr2string(group_ref, group_ref_size, group_ref_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->group_ref.setValue(group_ref_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_group_ref(functiongroup_Ptr functiongroup_hdl, char * group_ref, int group_ref_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->group_ref.getInheritedValue(), group_ref, group_ref_size))
      ERROR("void cxios_get_functiongroup_group_ref(functiongroup_Ptr functiongroup_hdl, char * group_ref, int group_ref_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_group_ref(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->group_ref.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_long_name(functiongroup_Ptr functiongroup_hdl, const char * long_name, int long_name_size)
  {
    std::string long_name_str;
    if (!cstr2string(long_name, long_name_size, long_name_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->long_name.setValue(long_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_long_name(functiongroup_Ptr functiongroup_hdl, char * long_name, int long_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->long_name.getInheritedValue(), long_name, long_name_size))
      ERROR("void cxios_get_functiongroup_long_name(functiongroup_Ptr functiongroup_hdl, char * long_name, int long_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_long_name(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->long_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_name(functiongroup_Ptr functiongroup_hdl, const char * name, int name_size)
  {
    std::string name_str;
    if (!cstr2string(name, name_size, name_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->name.setValue(name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_name(functiongroup_Ptr functiongroup_hdl, char * name, int name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->name.getInheritedValue(), name, name_size))
      ERROR("void cxios_get_functiongroup_name(functiongroup_Ptr functiongroup_hdl, char * name, int name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_name(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_offload(functiongroup_Ptr functiongroup_hdl, const char * offload, int offload_size)
  {
    std::string offload_str;
    if (!cstr2string(offload, offload_size, offload_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->offload.setValue(offload_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_offload(functiongroup_Ptr functiongroup_hdl, char * offload, int offload_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->offload.getInheritedValue(), offload, offload_size))
      ERROR("void cxios_get_functiongroup_offload(functiongroup_Ptr functiongroup_hdl, char * offload, int offload_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_offload(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->offload.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_offset(functiongroup_Ptr functiongroup_hdl, cxios_duration offset_c)
  {
    CTimer::get("XIOS").resume();
    functiongroup_hdl->offset.allocate();
    CDuration& offset = functiongroup_hdl->offset.get();
    offset.year = offset_c.year;
    offset.month = offset_c.month;
    offset.day = offset_c.day;
    offset.hour = offset_c.hour;
    offset.minute = offset_c.minute;
    offset.second = offset_c.second;
    offset.timestep = offset_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_offset(functiongroup_Ptr functiongroup_hdl, cxios_duration* offset_c)
  {
    CTimer::get("XIOS").resume();
    CDuration offset = functiongroup_hdl->offset.getInheritedValue();
    offset_c->year = offset.year;
    offset_c->month = offset.month;
    offset_c->day = offset.day;
    offset_c->hour = offset.hour;
    offset_c->minute = offset.minute;
    offset_c->second = offset.second;
    offset_c->timestep = offset.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_offset(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_pool_offload(functiongroup_Ptr functiongroup_hdl, const char * pool_offload, int pool_offload_size)
  {
    std::string pool_offload_str;
    if (!cstr2string(pool_offload, pool_offload_size, pool_offload_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->pool_offload.setValue(pool_offload_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_pool_offload(functiongroup_Ptr functiongroup_hdl, char * pool_offload, int pool_offload_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->pool_offload.getInheritedValue(), pool_offload, pool_offload_size))
      ERROR("void cxios_get_functiongroup_pool_offload(functiongroup_Ptr functiongroup_hdl, char * pool_offload, int pool_offload_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_pool_offload(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->pool_offload.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_pysrc(functiongroup_Ptr functiongroup_hdl, const char * pysrc, int pysrc_size)
  {
    std::string pysrc_str;
    if (!cstr2string(pysrc, pysrc_size, pysrc_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->pysrc.setValue(pysrc_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_pysrc(functiongroup_Ptr functiongroup_hdl, char * pysrc, int pysrc_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->pysrc.getInheritedValue(), pysrc, pysrc_size))
      ERROR("void cxios_get_functiongroup_pysrc(functiongroup_Ptr functiongroup_hdl, char * pysrc, int pysrc_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_pysrc(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->pysrc.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_functiongroup_standard_name(functiongroup_Ptr functiongroup_hdl, const char * standard_name, int standard_name_size)
  {
    std::string standard_name_str;
    if (!cstr2string(standard_name, standard_name_size, standard_name_str)) return;
    CTimer::get("XIOS").resume();
    functiongroup_hdl->standard_name.setValue(standard_name_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_functiongroup_standard_name(functiongroup_Ptr functiongroup_hdl, char * standard_name, int standard_name_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(functiongroup_hdl->standard_name.getInheritedValue(), standard_name, standard_name_size))
      ERROR("void cxios_get_functiongroup_standard_name(functiongroup_Ptr functiongroup_hdl, char * standard_name, int standard_name_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_functiongroup_standard_name(functiongroup_Ptr functiongroup_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = functiongroup_hdl->standard_name.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
