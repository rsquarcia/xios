# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class FieldGroup(Object): 
  _object_type = 'fieldgroup'
  FIELD_META = {
  'fieldgroup_id': {'type': str},
  'add_offset': {'type': float},
  'axis_ref': {'type': str},
  'build_workflow_graph': {'type': bool},
  'cell_methods': {'type': str},
  'cell_methods_mode': {'type': str},
  'check_if_active': {'type': bool},
  'chunking_blocksize_target': {'type': float},
  'comment': {'type': str},
  'compression_level': {'type': int},
  'compression_params': {'type': np.ndarray, 'array_type': float, 'ndim': 1},
  'compression_type': {'type': str},
  'conversion_by_netcdf': {'type': bool},
  'default_value': {'type': float},
  'detect_missing_value': {'type': bool},
  'domain_ref': {'type': str},
  'enabled': {'type': bool},
  'expr': {'type': str},
  'field_ref': {'type': str},
  'freq_offset': {'type': Duration},
  'freq_op': {'type': Duration},
  'grid_path': {'type': str},
  'grid_ref': {'type': str},
  'group_ref': {'type': str},
  'indexed_output': {'type': bool},
  'level': {'type': int},
  'long_name': {'type': str},
  'name': {'type': str},
  'operation': {'type': str},
  'prec': {'type': int},
  'read_access': {'type': bool},
  'scalar_ref': {'type': str},
  'scale_factor': {'type': float},
  'standard_name': {'type': str},
  'ts_enabled': {'type': bool},
  'ts_split_freq': {'type': Duration},
  'unit': {'type': str},
  'valid_max': {'type': float},
  'valid_min': {'type': float},
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
  
  
  

