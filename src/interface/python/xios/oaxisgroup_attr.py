# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class AxisGroup(Object): 
  _object_type = 'axisgroup'
  FIELD_META = {
  'axisgroup_id': {'type': str},
  'axis_ref': {'type': str},
  'axis_type': {'type': str},
  'begin': {'type': int},
  'bounds': {'type': np.ndarray, 'array_type': float, 'ndim': 2},
  'bounds_name': {'type': str},
  'chunking_weight': {'type': float},
  'comment': {'type': str},
  'convert_from_factor': {'type': float},
  'data_begin': {'type': int},
  'data_index': {'type': np.ndarray, 'array_type': int, 'ndim': 1},
  'data_n': {'type': int},
  'dim_name': {'type': str},
  'formula': {'type': str},
  'formula_bounds': {'type': str},
  'formula_term': {'type': str},
  'formula_term_bounds': {'type': str},
  'group_ref': {'type': str},
  'index': {'type': np.ndarray, 'array_type': int, 'ndim': 1},
  'label': {'type': str},
  'long_name': {'type': str},
  'mask': {'type': np.ndarray, 'array_type': bool, 'ndim': 1},
  'n': {'type': int},
  'n_distributed_partition': {'type': int},
  'n_glo': {'type': int},
  'name': {'type': str},
  'positive': {'type': str},
  'prec': {'type': int},
  'standard_name': {'type': str},
  'unit': {'type': str},
  'value': {'type': np.ndarray, 'array_type': float, 'ndim': 1},
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
  
  @property
  def context_id(self):
    return self._context_id
  
  def set_attr(self, **kwargs):
    current_context_id = swipswap_ctx(self._context_id)
    for key, value in kwargs.items():
      if key in self.FIELD_META:
        setattr(self, key, value)
      else:
        raise AttributeError(f'Unknown attribute {key} for class {self.__class__.__name__}')
    swipswap_ctx(current_context_id)
  
  

