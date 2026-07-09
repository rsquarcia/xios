# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class FunctionGroup(Object): 
  _object_type = 'functiongroup'
  FIELD_META = {
  'functiongroup_id': {'type': str},
  'argin': {'type': str},
  'argout': {'type': str},
  'comment': {'type': str},
  'expr': {'type': str},
  'group_ref': {'type': str},
  'long_name': {'type': str},
  'name': {'type': str},
  'offload': {'type': str},
  'pool_offload': {'type': str},
  'pysrc': {'type': str},
  'standard_name': {'type': str},
  }
  
  def __init__(self, id = None, **kwargs):
    self._context_id = String()
    get_current_context_id(self._context_id)
    super().__init__(id)
    for key, value in kwargs.items():
      if key in self.FIELD_META:
        setattr(self, key, value)
      else: 
        raise AttributeError(f"Unknown attribute '{key}' for class '{self.__class__.__name__}'")
  
  
  

