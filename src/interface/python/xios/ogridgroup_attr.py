# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class GridGroup(Object): 
  _object_type = 'gridgroup'
  FIELD_META = {
  'gridgroup_id': {'type': str},
  'comment': {'type': str},
  'description': {'type': str},
  'group_ref': {'type': str},
  'mask_0d': {'type': np.ndarray, 'array_type': bool, 'ndim': 1},
  'mask_1d': {'type': np.ndarray, 'array_type': bool, 'ndim': 1},
  'mask_2d': {'type': np.ndarray, 'array_type': bool, 'ndim': 2},
  'mask_3d': {'type': np.ndarray, 'array_type': bool, 'ndim': 3},
  'mask_4d': {'type': np.ndarray, 'array_type': bool, 'ndim': 4},
  'mask_5d': {'type': np.ndarray, 'array_type': bool, 'ndim': 5},
  'mask_6d': {'type': np.ndarray, 'array_type': bool, 'ndim': 6},
  'mask_7d': {'type': np.ndarray, 'array_type': bool, 'ndim': 7},
  'name': {'type': str},
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
  
  
  

