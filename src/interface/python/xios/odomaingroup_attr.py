# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class DomainGroup(Object): 
  _object_type = 'domaingroup'
  FIELD_META = {
  'domaingroup_id': {'type': str},
  'area': {'type': np.ndarray, 'array_type': float, 'ndim': 2},
  'area_1d': {'type': np.ndarray, 'array_type': float, 'ndim': 1},
  'area_2d': {'type': np.ndarray, 'array_type': float, 'ndim': 2},
  'bounds_lat_1d': {'type': np.ndarray, 'array_type': float, 'ndim': 2},
  'bounds_lat_2d': {'type': np.ndarray, 'array_type': float, 'ndim': 3},
  'bounds_lat_name': {'type': str},
  'bounds_lon_1d': {'type': np.ndarray, 'array_type': float, 'ndim': 2},
  'bounds_lon_2d': {'type': np.ndarray, 'array_type': float, 'ndim': 3},
  'bounds_lon_name': {'type': str},
  'chunking_weight_i': {'type': float},
  'chunking_weight_j': {'type': float},
  'comment': {'type': str},
  'data_dim': {'type': int},
  'data_i_index': {'type': np.ndarray, 'array_type': int, 'ndim': 1},
  'data_ibegin': {'type': int},
  'data_j_index': {'type': np.ndarray, 'array_type': int, 'ndim': 1},
  'data_jbegin': {'type': int},
  'data_ni': {'type': int},
  'data_nj': {'type': int},
  'dim_i_name': {'type': str},
  'dim_j_name': {'type': str},
  'domain_ref': {'type': str},
  'group_ref': {'type': str},
  'i_index': {'type': np.ndarray, 'array_type': int, 'ndim': 1},
  'ibegin': {'type': int},
  'j_index': {'type': np.ndarray, 'array_type': int, 'ndim': 1},
  'jbegin': {'type': int},
  'lat_name': {'type': str},
  'latvalue_1d': {'type': np.ndarray, 'array_type': float, 'ndim': 1},
  'latvalue_2d': {'type': np.ndarray, 'array_type': float, 'ndim': 2},
  'lon_name': {'type': str},
  'long_name': {'type': str},
  'lonvalue_1d': {'type': np.ndarray, 'array_type': float, 'ndim': 1},
  'lonvalue_2d': {'type': np.ndarray, 'array_type': float, 'ndim': 2},
  'mask_1d': {'type': np.ndarray, 'array_type': bool, 'ndim': 1},
  'mask_2d': {'type': np.ndarray, 'array_type': bool, 'ndim': 2},
  'name': {'type': str},
  'ni': {'type': int},
  'ni_glo': {'type': int},
  'nj': {'type': int},
  'nj_glo': {'type': int},
  'nvertex': {'type': int},
  'nvertex_name': {'type': str},
  'prec': {'type': int},
  'radius': {'type': float},
  'standard_name': {'type': str},
  'type': {'type': str},
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
  
  

