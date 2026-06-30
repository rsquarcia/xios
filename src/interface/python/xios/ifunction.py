from ctypes import c_char_p, c_int, c_bool, POINTER, string_at, byref, pointer
from xios.config import lib, String, Bool, typecheck
from xios.ofunction_attr import Function
from xios.ofunctiongroup_attr import FunctionGroup
from typing import Union



#_____________________________________________________________________________________________#
#                                    #C functions definitions                                 #
#_____________________________________________________________________________________________#

lib.cxios_function_handle_create.argtypes = [POINTER(Function), c_char_p, c_int]
lib.cxios_function_handle_create.restype = None

lib.cxios_functiongroup_handle_create.argtypes = [POINTER(FunctionGroup), c_char_p, c_int]
lib.cxios_functiongroup_handle_create.restype = None

lib.cxios_function_valid_id.argtypes = [POINTER(c_bool), c_char_p, c_int]
lib.cxios_function_valid_id.restype = None

lib.cxios_functiongroup_valid_id.argtypes = [POINTER(c_bool), c_char_p, c_int]
lib.cxios_functiongroup_valid_id.restype = None

#__________________________________________________________________________________________________#
#                                      INTERFACE FUNCTIONS                                         #
#__________________________________________________________________________________________________#

@typecheck
def get_function_handle(idt: Union[str, String], ret: Function) -> None:
    idt = String(idt)

    idt_c = idt._c_value
    len_idt_c = len(string_at(idt_c))

    lib.cxios_function_handle_create(byref(ret), idt_c, len_idt_c)

@typecheck
def get_functiongroup_handle(idt: Union[str, String], ret: FunctionGroup) -> None:
    idt = String(idt)

    idt_c = idt._c_value
    len_idt_c = len(string_at(idt_c))

    lib.cxios_functiongroup_handle_create(byref(ret), idt_c, len_idt_c)

@typecheck
def is_valid_function(idt: Union[str, String]) -> bool:
    idt = String(idt)
    is_val = Bool(False)

    idt_c = idt._c_value
    len_idt_c = len(string_at(idt_c))
    is_val_c = pointer(is_val._c_value)

    lib.cxios_function_valid_id(is_val_c, idt_c, len_idt_c)

    return bool(is_val_c.contents)

@typecheck
def is_valid_functiongroup(idt: Union[str, String]) -> bool:
    idt = String(idt)
    is_val = Bool(False)

    idt_c = idt._c_value
    len_idt_c = len(string_at(idt_c))
    is_val_c = pointer(is_val._c_value)

    lib.cxios_functiongroup_valid_id(is_val_c, idt_c, len_idt_c)

    return bool(is_val_c.contents)
