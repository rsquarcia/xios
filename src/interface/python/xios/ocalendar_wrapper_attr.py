# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class CalendarWrapper(Object): 
  _object_type = 'calendar_wrapper'
  FIELD_META = {
  'calendar_wrapper_id': {'type': str},
  'comment': {'type': str},
  'day_length': {'type': int},
  'leap_year_drift': {'type': float},
  'leap_year_drift_offset': {'type': float},
  'leap_year_month': {'type': int},
  'month_lengths': {'type': np.ndarray, 'array_type': int, 'ndim': 1},
  'start_date': {'type': str},
  'time_origin': {'type': str},
  'timestep': {'type': Duration},
  'type': {'type': str},
  'year_length': {'type': int},
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
  
  

