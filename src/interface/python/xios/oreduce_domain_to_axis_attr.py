# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class ReduceDomainToAxis(Object): 
  _object_type = 'reduce_domain_to_axis'
  FIELD_META = {
  'reduce_domain_to_axis_id': {'type': str},
  'direction': {'type': str},
  'local': {'type': bool},
  'operation': {'type': str},
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
  
  
  

