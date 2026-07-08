# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

import ctypes
import numpy as np
from typing import Union, Optional
from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.iduration import Duration
from xios.idate import Date
from xios.ifunction import  get_function_handle
from xios.ofunction_attr import Function

#_____________________________________________________________________________________________#
#                                    #C function definitions                                  #
#_____________________________________________________________________________________________#



lib.cxios_get_function_argin.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_function_argin.restype = None

lib.cxios_set_function_argin.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_function_argin.restype = None

lib.cxios_is_defined_function_argin.argtypes = [Function]
lib.cxios_is_defined_function_argin.restype = ctypes.c_bool

lib.cxios_get_function_argout.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_function_argout.restype = None

lib.cxios_set_function_argout.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_function_argout.restype = None

lib.cxios_is_defined_function_argout.argtypes = [Function]
lib.cxios_is_defined_function_argout.restype = ctypes.c_bool

lib.cxios_get_function_comment.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_function_comment.restype = None

lib.cxios_set_function_comment.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_function_comment.restype = None

lib.cxios_is_defined_function_comment.argtypes = [Function]
lib.cxios_is_defined_function_comment.restype = ctypes.c_bool

lib.cxios_get_function_expr.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_function_expr.restype = None

lib.cxios_set_function_expr.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_function_expr.restype = None

lib.cxios_is_defined_function_expr.argtypes = [Function]
lib.cxios_is_defined_function_expr.restype = ctypes.c_bool

lib.cxios_get_function_long_name.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_function_long_name.restype = None

lib.cxios_set_function_long_name.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_function_long_name.restype = None

lib.cxios_is_defined_function_long_name.argtypes = [Function]
lib.cxios_is_defined_function_long_name.restype = ctypes.c_bool

lib.cxios_get_function_name.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_function_name.restype = None

lib.cxios_set_function_name.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_function_name.restype = None

lib.cxios_is_defined_function_name.argtypes = [Function]
lib.cxios_is_defined_function_name.restype = ctypes.c_bool

lib.cxios_get_function_standard_name.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_get_function_standard_name.restype = None

lib.cxios_set_function_standard_name.argtypes = [Function, ctypes.c_char_p, ctypes.c_int]
lib.cxios_set_function_standard_name.restype = None

lib.cxios_is_defined_function_standard_name.argtypes = [Function]
lib.cxios_is_defined_function_standard_name.restype = ctypes.c_bool

#_____________________________________________________________________________________________#
#                                   #C interface functions                                    #
#_____________________________________________________________________________________________#

@typecheck
def set_function_attr(function_id : Union[String, str], argin : Optional[Union[str, String]] = None, argout : Optional[Union[str, String]] = None,   
comment : Optional[Union[str, String]] = None, expr : Optional[Union[str, String]] = None,   
long_name : Optional[Union[str, String]] = None, name : Optional[Union[str, String]] = None,   
standard_name : Optional[Union[str, String]] = None):

  
  function_hdl = Function()
  

  get_function_handle(function_id, function_hdl)
  set_function_attr_hdl_(function_hdl, argin, argout, comment, expr, long_name, name, standard_name)
  return 



@typecheck
def set_function_attr_hdl(function_hdl : Function, argin : Optional[Union[str, String]] = None, argout : Optional[Union[str, String]] = None,   
comment : Optional[Union[str, String]] = None, expr : Optional[Union[str, String]] = None,   
long_name : Optional[Union[str, String]] = None, name : Optional[Union[str, String]] = None,   
standard_name : Optional[Union[str, String]] = None):

  
  set_function_attr_hdl_(function_hdl, argin, argout, comment, expr, long_name, name, standard_name)
  return 



@typecheck
def set_function_attr_hdl_(function_hdl : Function, argin_ : Optional[Union[str, String]] = None, argout_ : Optional[Union[str, String]] = None,   
comment_ : Optional[Union[str, String]] = None, expr_ : Optional[Union[str, String]] = None,   
long_name_ : Optional[Union[str, String]] = None, name_ : Optional[Union[str, String]] = None,   
standard_name_ : Optional[Union[str, String]] = None):

  
  

  if argin_ is not None:
  
    argin_= String(argin_)
    argin_c = argin_._c_value
    len_argin_c = len(ctypes.string_at(argin_c))
    lib.cxios_set_function_argin(function_hdl, argin_c, len_argin_c)
    
  

  if argout_ is not None:
  
    argout_= String(argout_)
    argout_c = argout_._c_value
    len_argout_c = len(ctypes.string_at(argout_c))
    lib.cxios_set_function_argout(function_hdl, argout_c, len_argout_c)
    
  

  if comment_ is not None:
  
    comment_= String(comment_)
    comment_c = comment_._c_value
    len_comment_c = len(ctypes.string_at(comment_c))
    lib.cxios_set_function_comment(function_hdl, comment_c, len_comment_c)
    
  

  if expr_ is not None:
  
    expr_= String(expr_)
    expr_c = expr_._c_value
    len_expr_c = len(ctypes.string_at(expr_c))
    lib.cxios_set_function_expr(function_hdl, expr_c, len_expr_c)
    
  

  if long_name_ is not None:
  
    long_name_= String(long_name_)
    long_name_c = long_name_._c_value
    len_long_name_c = len(ctypes.string_at(long_name_c))
    lib.cxios_set_function_long_name(function_hdl, long_name_c, len_long_name_c)
    
  

  if name_ is not None:
  
    name_= String(name_)
    name_c = name_._c_value
    len_name_c = len(ctypes.string_at(name_c))
    lib.cxios_set_function_name(function_hdl, name_c, len_name_c)
    
  

  if standard_name_ is not None:
  
    standard_name_= String(standard_name_)
    standard_name_c = standard_name_._c_value
    len_standard_name_c = len(ctypes.string_at(standard_name_c))
    lib.cxios_set_function_standard_name(function_hdl, standard_name_c, len_standard_name_c)
    
  
  return 



@typecheck
def get_function_attr(function_id : Union[String, str], argin : Optional[String] = None, argout : Optional[String] = None,   
comment : Optional[String] = None, expr : Optional[String] = None, long_name : Optional[String] = None,   
name : Optional[String] = None, standard_name : Optional[String] = None):

  
  function_hdl = Function()
  

  get_function_handle(function_id, function_hdl)
  get_function_attr_hdl_(function_hdl, argin, argout, comment, expr, long_name, name, standard_name)
  return 



@typecheck
def get_function_attr_hdl(function_hdl : Function, argin : Optional[String] = None, argout : Optional[String] = None,   
comment : Optional[String] = None, expr : Optional[String] = None, long_name : Optional[String] = None,   
name : Optional[String] = None, standard_name : Optional[String] = None):

  
  get_function_attr_hdl_(function_hdl, argin, argout, comment, expr, long_name, name, standard_name)
  return 



@typecheck
def get_function_attr_hdl_(function_hdl : Function, argin_ : Optional[String] = None, argout_ : Optional[String] = None,   
comment_ : Optional[String] = None, expr_ : Optional[String] = None, long_name_ : Optional[String] = None,   
name_ : Optional[String] = None, standard_name_ : Optional[String] = None):

  
  

  if argin_ is not None:
  
    argin_c = argin_._c_value
    len_argin_c = len(ctypes.string_at(argin_c))
    lib.cxios_get_function_argin(function_hdl, argin_c, len_argin_c)
    
  

  if argout_ is not None:
  
    argout_c = argout_._c_value
    len_argout_c = len(ctypes.string_at(argout_c))
    lib.cxios_get_function_argout(function_hdl, argout_c, len_argout_c)
    
  

  if comment_ is not None:
  
    comment_c = comment_._c_value
    len_comment_c = len(ctypes.string_at(comment_c))
    lib.cxios_get_function_comment(function_hdl, comment_c, len_comment_c)
    
  

  if expr_ is not None:
  
    expr_c = expr_._c_value
    len_expr_c = len(ctypes.string_at(expr_c))
    lib.cxios_get_function_expr(function_hdl, expr_c, len_expr_c)
    
  

  if long_name_ is not None:
  
    long_name_c = long_name_._c_value
    len_long_name_c = len(ctypes.string_at(long_name_c))
    lib.cxios_get_function_long_name(function_hdl, long_name_c, len_long_name_c)
    
  

  if name_ is not None:
  
    name_c = name_._c_value
    len_name_c = len(ctypes.string_at(name_c))
    lib.cxios_get_function_name(function_hdl, name_c, len_name_c)
    
  

  if standard_name_ is not None:
  
    standard_name_c = standard_name_._c_value
    len_standard_name_c = len(ctypes.string_at(standard_name_c))
    lib.cxios_get_function_standard_name(function_hdl, standard_name_c, len_standard_name_c)
    
  
  return 



@typecheck
def is_defined_function_attr(function_id : String, argin : Optional[Bool] = None, argout : Optional[Bool] = None, comment : Optional[Bool] = None,   
expr : Optional[Bool] = None, long_name : Optional[Bool] = None, name : Optional[Bool] = None,   
standard_name : Optional[Bool] = None):

  
  function_hdl = Function()
  

  get_function_handle(function_id, function_hdl)
  is_defined_function_attr_hdl_(function_hdl, argin, argout, comment, expr, long_name, name, standard_name)
  return 



@typecheck
def is_defined_function_attr_hdl(function_hdl : Function, argin : Optional[Bool] = None, argout : Optional[Bool] = None, comment : Optional[Bool] = None,   
expr : Optional[Bool] = None, long_name : Optional[Bool] = None, name : Optional[Bool] = None,   
standard_name : Optional[Bool] = None):

  
  is_defined_function_attr_hdl_(function_hdl, argin, argout, comment, expr, long_name, name, standard_name)
  return 



@typecheck
def is_defined_function_attr_hdl_(function_hdl : Function, argin_ : Optional[Bool] = None, argout_ : Optional[Bool] = None,   
comment_ : Optional[Bool] = None, expr_ : Optional[Bool] = None, long_name_ : Optional[Bool] = None,   
name_ : Optional[Bool] = None, standard_name_ : Optional[Bool] = None):

  
  

  if argin_  is not None:
    argin_c = lib.cxios_is_defined_function_argin(function_hdl)
    argin_._c_value = ctypes.c_bool(argin_c)
    
  

  if argout_  is not None:
    argout_c = lib.cxios_is_defined_function_argout(function_hdl)
    argout_._c_value = ctypes.c_bool(argout_c)
    
  

  if comment_  is not None:
    comment_c = lib.cxios_is_defined_function_comment(function_hdl)
    comment_._c_value = ctypes.c_bool(comment_c)
    
  

  if expr_  is not None:
    expr_c = lib.cxios_is_defined_function_expr(function_hdl)
    expr_._c_value = ctypes.c_bool(expr_c)
    
  

  if long_name_  is not None:
    long_name_c = lib.cxios_is_defined_function_long_name(function_hdl)
    long_name_._c_value = ctypes.c_bool(long_name_c)
    
  

  if name_  is not None:
    name_c = lib.cxios_is_defined_function_name(function_hdl)
    name_._c_value = ctypes.c_bool(name_c)
    
  

  if standard_name_  is not None:
    standard_name_c = lib.cxios_is_defined_function_standard_name(function_hdl)
    standard_name_._c_value = ctypes.c_bool(standard_name_c)
    
  
  return 



