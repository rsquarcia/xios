# * ************************************************************************** *
# *               Interface auto generated - do not modify                     *
# * ************************************************************************** *

from xios.config import lib, typecheck, String, Bool, Int, NpArrayInt, NpArrayBool, NpArray, Double
from xios.obj import Object, swipswap_ctx
from xios.icontext import get_current_context_id, set_current_context
from xios.idate import Date
from xios.iduration import Duration
import numpy as np


class GenerateRectilinearDomain(Object): 
  _object_type = 'generate_rectilinear_domain'
  FIELD_META = {
  'generate_rectilinear_domain_id': {'type': str},
  'bounds_lat_end': {'type': float},
  'bounds_lat_start': {'type': float},
  'bounds_lon_end': {'type': float},
  'bounds_lon_start': {'type': float},
  'lat_end': {'type': float},
  'lat_start': {'type': float},
  'lon_end': {'type': float},
  'lon_start': {'type': float},
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
  
  
  

