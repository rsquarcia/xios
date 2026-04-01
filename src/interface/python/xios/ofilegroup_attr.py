# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class FileGroup(Object): 
  _object_type = 'filegroup'
  FIELD_META = {
  'filegroup_id': {'type': str},
  'append': {'type': bool},
  'comment': {'type': str},
  'compression_level': {'type': int},
  'convention': {'type': str},
  'convention_str': {'type': str},
  'cyclic': {'type': bool},
  'description': {'type': str},
  'enabled': {'type': bool},
  'format': {'type': str},
  'gatherer': {'type': str},
  'group_ref': {'type': str},
  'min_digits': {'type': int},
  'mode': {'type': str},
  'name': {'type': str},
  'name_suffix': {'type': str},
  'output_freq': {'type': Duration},
  'output_level': {'type': int},
  'par_access': {'type': str},
  'pool_gatherer': {'type': str},
  'pool_reader': {'type': str},
  'pool_writer': {'type': str},
  'read_metadata_par': {'type': bool},
  'reader': {'type': str},
  'record_offset': {'type': int},
  'split_end_offset': {'type': Duration},
  'split_freq': {'type': Duration},
  'split_freq_format': {'type': str},
  'split_last_date': {'type': str},
  'split_start_offset': {'type': Duration},
  'sync_freq': {'type': Duration},
  'time_counter': {'type': str},
  'time_counter_name': {'type': str},
  'time_stamp_format': {'type': str},
  'time_stamp_name': {'type': str},
  'time_units': {'type': str},
  'timeseries': {'type': str},
  'ts_prefix': {'type': str},
  'type': {'type': str},
  'using_server2': {'type': bool},
  'uuid_format': {'type': str},
  'uuid_name': {'type': str},
  'writer': {'type': str},
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
  
  

