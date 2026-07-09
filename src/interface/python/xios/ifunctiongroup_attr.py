# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

import ctypes
import numpy as np
from typing import Union, Optional
from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.iduration import Duration
from xios.idate import Date
from xios.ifunction import  get_functiongroup_handle
from xios.ofunctiongroup_attr import FunctionGroup

#_____________________________________________________________________________________________#
#                                    #C function definitions                                  #
#_____________________________________________________________________________________________#



lib.cxios_get_functiongroup_argin.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_argin.restype = None

lib.cxios_set_functiongroup_argin.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_argin.restype = None

lib.cxios_is_defined_functiongroup_argin.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_argin.restype = ctypes.c_bool

lib.cxios_get_functiongroup_argout.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_argout.restype = None

lib.cxios_set_functiongroup_argout.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_argout.restype = None

lib.cxios_is_defined_functiongroup_argout.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_argout.restype = ctypes.c_bool

lib.cxios_get_functiongroup_comment.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_comment.restype = None

lib.cxios_set_functiongroup_comment.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_comment.restype = None

lib.cxios_is_defined_functiongroup_comment.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_comment.restype = ctypes.c_bool

lib.cxios_get_functiongroup_expr.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_expr.restype = None

lib.cxios_set_functiongroup_expr.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_expr.restype = None

lib.cxios_is_defined_functiongroup_expr.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_expr.restype = ctypes.c_bool

lib.cxios_get_functiongroup_group_ref.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_group_ref.restype = None

lib.cxios_set_functiongroup_group_ref.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_group_ref.restype = None

lib.cxios_is_defined_functiongroup_group_ref.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_group_ref.restype = ctypes.c_bool

lib.cxios_get_functiongroup_long_name.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_long_name.restype = None

lib.cxios_set_functiongroup_long_name.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_long_name.restype = None

lib.cxios_is_defined_functiongroup_long_name.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_long_name.restype = ctypes.c_bool

lib.cxios_get_functiongroup_name.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_name.restype = None

lib.cxios_set_functiongroup_name.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_name.restype = None

lib.cxios_is_defined_functiongroup_name.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_name.restype = ctypes.c_bool

lib.cxios_get_functiongroup_offload.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_offload.restype = None

lib.cxios_set_functiongroup_offload.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_offload.restype = None

lib.cxios_is_defined_functiongroup_offload.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_offload.restype = ctypes.c_bool

lib.cxios_get_functiongroup_pool_offload.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_pool_offload.restype = None

lib.cxios_set_functiongroup_pool_offload.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_pool_offload.restype = None

lib.cxios_is_defined_functiongroup_pool_offload.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_pool_offload.restype = ctypes.c_bool

lib.cxios_get_functiongroup_pysrc.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_pysrc.restype = None

lib.cxios_set_functiongroup_pysrc.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_pysrc.restype = None

lib.cxios_is_defined_functiongroup_pysrc.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_pysrc.restype = ctypes.c_bool

lib.cxios_get_functiongroup_standard_name.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_functiongroup_standard_name.restype = None

lib.cxios_set_functiongroup_standard_name.argtypes = [FunctionGroup, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_functiongroup_standard_name.restype = None

lib.cxios_is_defined_functiongroup_standard_name.argtypes = [FunctionGroup]
lib.cxios_is_defined_functiongroup_standard_name.restype = ctypes.c_bool

#_____________________________________________________________________________________________#
#                                   #C interface functions                                    #
#_____________________________________________________________________________________________#

@typecheck
def set_functiongroup_attr(functiongroup_id : Union[String, str], argin : Optional[Union[str, String]] = None, argout : Optional[Union[str, String]] = None,   
comment : Optional[Union[str, String]] = None, expr : Optional[Union[str, String]] = None,   
group_ref : Optional[Union[str, String]] = None, long_name : Optional[Union[str, String]] = None,   
name : Optional[Union[str, String]] = None, offload : Optional[Union[str, String]] = None,   
pool_offload : Optional[Union[str, String]] = None, pysrc : Optional[Union[str, String]] = None,   
standard_name : Optional[Union[str, String]] = None):

  
  functiongroup_hdl = FunctionGroup()
  

  get_functiongroup_handle(functiongroup_id, functiongroup_hdl)
  set_functiongroup_attr_hdl_(functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, offload, pool_offload,  
   pysrc, standard_name)
  return 



@typecheck
def set_functiongroup_attr_hdl(functiongroup_hdl : FunctionGroup, argin : Optional[Union[str, String]] = None, argout : Optional[Union[str, String]] = None,   
comment : Optional[Union[str, String]] = None, expr : Optional[Union[str, String]] = None,   
group_ref : Optional[Union[str, String]] = None, long_name : Optional[Union[str, String]] = None,   
name : Optional[Union[str, String]] = None, offload : Optional[Union[str, String]] = None,   
pool_offload : Optional[Union[str, String]] = None, pysrc : Optional[Union[str, String]] = None,   
standard_name : Optional[Union[str, String]] = None):

  
  set_functiongroup_attr_hdl_(functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, offload, pool_offload,  
   pysrc, standard_name)
  return 



@typecheck
def set_functiongroup_attr_hdl_(functiongroup_hdl : FunctionGroup, argin_ : Optional[Union[str, String]] = None, argout_ : Optional[Union[str, String]] = None,   
comment_ : Optional[Union[str, String]] = None, expr_ : Optional[Union[str, String]] = None,   
group_ref_ : Optional[Union[str, String]] = None, long_name_ : Optional[Union[str, String]] = None,   
name_ : Optional[Union[str, String]] = None, offload_ : Optional[Union[str, String]] = None,   
pool_offload_ : Optional[Union[str, String]] = None, pysrc_ : Optional[Union[str, String]] = None,   
standard_name_ : Optional[Union[str, String]] = None):

  
  

  if argin_ is not None:
  
    argin_= String(argin_)
    argin_c = argin_._c_value
    len_argin_c = len(ctypes.string_at(argin_c))
    lib.cxios_set_functiongroup_argin(functiongroup_hdl, argin_c, len_argin_c)
    
  

  if argout_ is not None:
  
    argout_= String(argout_)
    argout_c = argout_._c_value
    len_argout_c = len(ctypes.string_at(argout_c))
    lib.cxios_set_functiongroup_argout(functiongroup_hdl, argout_c, len_argout_c)
    
  

  if comment_ is not None:
  
    comment_= String(comment_)
    comment_c = comment_._c_value
    len_comment_c = len(ctypes.string_at(comment_c))
    lib.cxios_set_functiongroup_comment(functiongroup_hdl, comment_c, len_comment_c)
    
  

  if expr_ is not None:
  
    expr_= String(expr_)
    expr_c = expr_._c_value
    len_expr_c = len(ctypes.string_at(expr_c))
    lib.cxios_set_functiongroup_expr(functiongroup_hdl, expr_c, len_expr_c)
    
  

  if group_ref_ is not None:
  
    group_ref_= String(group_ref_)
    group_ref_c = group_ref_._c_value
    len_group_ref_c = len(ctypes.string_at(group_ref_c))
    lib.cxios_set_functiongroup_group_ref(functiongroup_hdl, group_ref_c, len_group_ref_c)
    
  

  if long_name_ is not None:
  
    long_name_= String(long_name_)
    long_name_c = long_name_._c_value
    len_long_name_c = len(ctypes.string_at(long_name_c))
    lib.cxios_set_functiongroup_long_name(functiongroup_hdl, long_name_c, len_long_name_c)
    
  

  if name_ is not None:
  
    name_= String(name_)
    name_c = name_._c_value
    len_name_c = len(ctypes.string_at(name_c))
    lib.cxios_set_functiongroup_name(functiongroup_hdl, name_c, len_name_c)
    
  

  if offload_ is not None:
  
    offload_= String(offload_)
    offload_c = offload_._c_value
    len_offload_c = len(ctypes.string_at(offload_c))
    lib.cxios_set_functiongroup_offload(functiongroup_hdl, offload_c, len_offload_c)
    
  

  if pool_offload_ is not None:
  
    pool_offload_= String(pool_offload_)
    pool_offload_c = pool_offload_._c_value
    len_pool_offload_c = len(ctypes.string_at(pool_offload_c))
    lib.cxios_set_functiongroup_pool_offload(functiongroup_hdl, pool_offload_c, len_pool_offload_c)
    
  

  if pysrc_ is not None:
  
    pysrc_= String(pysrc_)
    pysrc_c = pysrc_._c_value
    len_pysrc_c = len(ctypes.string_at(pysrc_c))
    lib.cxios_set_functiongroup_pysrc(functiongroup_hdl, pysrc_c, len_pysrc_c)
    
  

  if standard_name_ is not None:
  
    standard_name_= String(standard_name_)
    standard_name_c = standard_name_._c_value
    len_standard_name_c = len(ctypes.string_at(standard_name_c))
    lib.cxios_set_functiongroup_standard_name(functiongroup_hdl, standard_name_c, len_standard_name_c)
    
  
  return 



@typecheck
def get_functiongroup_attr(functiongroup_id : Union[String, str], argin : Optional[String] = None, argout : Optional[String] = None,   
comment : Optional[String] = None, expr : Optional[String] = None, group_ref : Optional[String] = None,   
long_name : Optional[String] = None, name : Optional[String] = None, offload : Optional[String] = None,   
pool_offload : Optional[String] = None, pysrc : Optional[String] = None, standard_name : Optional[String] = None):

  
  functiongroup_hdl = FunctionGroup()
  

  get_functiongroup_handle(functiongroup_id, functiongroup_hdl)
  get_functiongroup_attr_hdl_(functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, offload, pool_offload,  
   pysrc, standard_name)
  return 



@typecheck
def get_functiongroup_attr_hdl(functiongroup_hdl : FunctionGroup, argin : Optional[String] = None, argout : Optional[String] = None,   
comment : Optional[String] = None, expr : Optional[String] = None, group_ref : Optional[String] = None,   
long_name : Optional[String] = None, name : Optional[String] = None, offload : Optional[String] = None,   
pool_offload : Optional[String] = None, pysrc : Optional[String] = None, standard_name : Optional[String] = None):

  
  get_functiongroup_attr_hdl_(functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, offload, pool_offload,  
   pysrc, standard_name)
  return 



@typecheck
def get_functiongroup_attr_hdl_(functiongroup_hdl : FunctionGroup, argin_ : Optional[String] = None, argout_ : Optional[String] = None,   
comment_ : Optional[String] = None, expr_ : Optional[String] = None, group_ref_ : Optional[String] = None,   
long_name_ : Optional[String] = None, name_ : Optional[String] = None, offload_ : Optional[String] = None,   
pool_offload_ : Optional[String] = None, pysrc_ : Optional[String] = None, standard_name_ : Optional[String] = None):

  
  

  if argin_ is not None:
  
    argin_c = argin_._c_value
    len_argin_c = len(ctypes.string_at(argin_c))
    lib.cxios_get_functiongroup_argin(functiongroup_hdl, argin_c, len_argin_c)
    
  

  if argout_ is not None:
  
    argout_c = argout_._c_value
    len_argout_c = len(ctypes.string_at(argout_c))
    lib.cxios_get_functiongroup_argout(functiongroup_hdl, argout_c, len_argout_c)
    
  

  if comment_ is not None:
  
    comment_c = comment_._c_value
    len_comment_c = len(ctypes.string_at(comment_c))
    lib.cxios_get_functiongroup_comment(functiongroup_hdl, comment_c, len_comment_c)
    
  

  if expr_ is not None:
  
    expr_c = expr_._c_value
    len_expr_c = len(ctypes.string_at(expr_c))
    lib.cxios_get_functiongroup_expr(functiongroup_hdl, expr_c, len_expr_c)
    
  

  if group_ref_ is not None:
  
    group_ref_c = group_ref_._c_value
    len_group_ref_c = len(ctypes.string_at(group_ref_c))
    lib.cxios_get_functiongroup_group_ref(functiongroup_hdl, group_ref_c, len_group_ref_c)
    
  

  if long_name_ is not None:
  
    long_name_c = long_name_._c_value
    len_long_name_c = len(ctypes.string_at(long_name_c))
    lib.cxios_get_functiongroup_long_name(functiongroup_hdl, long_name_c, len_long_name_c)
    
  

  if name_ is not None:
  
    name_c = name_._c_value
    len_name_c = len(ctypes.string_at(name_c))
    lib.cxios_get_functiongroup_name(functiongroup_hdl, name_c, len_name_c)
    
  

  if offload_ is not None:
  
    offload_c = offload_._c_value
    len_offload_c = len(ctypes.string_at(offload_c))
    lib.cxios_get_functiongroup_offload(functiongroup_hdl, offload_c, len_offload_c)
    
  

  if pool_offload_ is not None:
  
    pool_offload_c = pool_offload_._c_value
    len_pool_offload_c = len(ctypes.string_at(pool_offload_c))
    lib.cxios_get_functiongroup_pool_offload(functiongroup_hdl, pool_offload_c, len_pool_offload_c)
    
  

  if pysrc_ is not None:
  
    pysrc_c = pysrc_._c_value
    len_pysrc_c = len(ctypes.string_at(pysrc_c))
    lib.cxios_get_functiongroup_pysrc(functiongroup_hdl, pysrc_c, len_pysrc_c)
    
  

  if standard_name_ is not None:
  
    standard_name_c = standard_name_._c_value
    len_standard_name_c = len(ctypes.string_at(standard_name_c))
    lib.cxios_get_functiongroup_standard_name(functiongroup_hdl, standard_name_c, len_standard_name_c)
    
  
  return 



@typecheck
def is_defined_functiongroup_attr(functiongroup_id : String, argin : Optional[Bool] = None, argout : Optional[Bool] = None,   
comment : Optional[Bool] = None, expr : Optional[Bool] = None, group_ref : Optional[Bool] = None,   
long_name : Optional[Bool] = None, name : Optional[Bool] = None, offload : Optional[Bool] = None,   
pool_offload : Optional[Bool] = None, pysrc : Optional[Bool] = None, standard_name : Optional[Bool] = None):

  
  functiongroup_hdl = FunctionGroup()
  

  get_functiongroup_handle(functiongroup_id, functiongroup_hdl)
  is_defined_functiongroup_attr_hdl_(functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, offload, pool_offload,  
   pysrc, standard_name)
  return 



@typecheck
def is_defined_functiongroup_attr_hdl(functiongroup_hdl : FunctionGroup, argin : Optional[Bool] = None, argout : Optional[Bool] = None,   
comment : Optional[Bool] = None, expr : Optional[Bool] = None, group_ref : Optional[Bool] = None,   
long_name : Optional[Bool] = None, name : Optional[Bool] = None, offload : Optional[Bool] = None,   
pool_offload : Optional[Bool] = None, pysrc : Optional[Bool] = None, standard_name : Optional[Bool] = None):

  
  is_defined_functiongroup_attr_hdl_(functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, offload, pool_offload,  
   pysrc, standard_name)
  return 



@typecheck
def is_defined_functiongroup_attr_hdl_(functiongroup_hdl : FunctionGroup, argin_ : Optional[Bool] = None, argout_ : Optional[Bool] = None,   
comment_ : Optional[Bool] = None, expr_ : Optional[Bool] = None, group_ref_ : Optional[Bool] = None,   
long_name_ : Optional[Bool] = None, name_ : Optional[Bool] = None, offload_ : Optional[Bool] = None,   
pool_offload_ : Optional[Bool] = None, pysrc_ : Optional[Bool] = None, standard_name_ : Optional[Bool] = None):

  
  

  if argin_  is not None:
    argin_c = lib.cxios_is_defined_functiongroup_argin(functiongroup_hdl)
    argin_._c_value = ctypes.c_bool(argin_c)
    
  

  if argout_  is not None:
    argout_c = lib.cxios_is_defined_functiongroup_argout(functiongroup_hdl)
    argout_._c_value = ctypes.c_bool(argout_c)
    
  

  if comment_  is not None:
    comment_c = lib.cxios_is_defined_functiongroup_comment(functiongroup_hdl)
    comment_._c_value = ctypes.c_bool(comment_c)
    
  

  if expr_  is not None:
    expr_c = lib.cxios_is_defined_functiongroup_expr(functiongroup_hdl)
    expr_._c_value = ctypes.c_bool(expr_c)
    
  

  if group_ref_  is not None:
    group_ref_c = lib.cxios_is_defined_functiongroup_group_ref(functiongroup_hdl)
    group_ref_._c_value = ctypes.c_bool(group_ref_c)
    
  

  if long_name_  is not None:
    long_name_c = lib.cxios_is_defined_functiongroup_long_name(functiongroup_hdl)
    long_name_._c_value = ctypes.c_bool(long_name_c)
    
  

  if name_  is not None:
    name_c = lib.cxios_is_defined_functiongroup_name(functiongroup_hdl)
    name_._c_value = ctypes.c_bool(name_c)
    
  

  if offload_  is not None:
    offload_c = lib.cxios_is_defined_functiongroup_offload(functiongroup_hdl)
    offload_._c_value = ctypes.c_bool(offload_c)
    
  

  if pool_offload_  is not None:
    pool_offload_c = lib.cxios_is_defined_functiongroup_pool_offload(functiongroup_hdl)
    pool_offload_._c_value = ctypes.c_bool(pool_offload_c)
    
  

  if pysrc_  is not None:
    pysrc_c = lib.cxios_is_defined_functiongroup_pysrc(functiongroup_hdl)
    pysrc_._c_value = ctypes.c_bool(pysrc_c)
    
  

  if standard_name_  is not None:
    standard_name_c = lib.cxios_is_defined_functiongroup_standard_name(functiongroup_hdl)
    standard_name_._c_value = ctypes.c_bool(standard_name_c)
    
  
  return 



