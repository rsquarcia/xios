from xios.ofield_attr import Field_
from xios.idata import send_field, receive_field
from xios.config import NpArray
from xios.obj import swipswap_ctx
from xios.oaxis_attr import Axis
from xios.odomain_attr import Domain
from xios.idomain import is_valid_domain
from xios.iaxis import is_valid_axis
import numpy as np

class Field(Field_):

    def __init__(self, id : str = None):
        super().__init__(id)
        self._data = None
        self._shape = None

    def send(self, data):
        current_context_id = swipswap_ctx(self._context_id)
        send_field(self._id, data)
        swipswap_ctx(current_context_id)

    def recv(self, data = None, shape = None):
        if data is None :
            if shape is None :
                data = NpArray(np.zeros(self.shape))
            else :
                data = NpArray(np.zeros(shape))
        else : data = NpArray(data)
        
        current_context_id = swipswap_ctx(self._context_id)
        receive_field(self._id, data)
        swipswap_ctx(current_context_id)
        return data.arr
    
    def _set_data(self, data):
        self._data = data

    @property
    def axis(self):
        return self.axes[0]
    
    @property
    def axes(self):
        return AxisAccessor(self._id)
    
    @property
    def domain(self):
        return self.domains[0]

    @property
    def domains(self):
        return DomainAccessor(self._id)
    
    @property
    def value(self, flatten = False):
        if self._data is not None and not flatten:
            return self._data
        elif self._data is not None:
            return self._data
        else :
            raise ValueError(f"There is no data available for this field. You must call that from a pythonFilter")
        
    @property
    def shape(self):
        j = 0
        shape = []
        curr = self.axes[0]
        while curr is not None:
            shape.append(self.axes[j].n)
            j=j+1
            curr = self.axes[j]

        curr = self.axes[0]
        j = 0
        while curr is not None:
            shape.append(self.domains[j].nj)
            shape.append(self.domains[j].ni)
            j=j+1
            curr = self.domains[j]

        self._shape = tuple(shape)
        return self._shape
            

    

class DomainAccessor:
    def __init__(self, field_id):
        self.field_id = field_id

    def _get_domain(self, idx):
        full_id = f"{self.field_id}::[{idx}]"
        if is_valid_domain(full_id):
            return Domain(full_id)
        return None

    def __getitem__(self, idx):
        return self._get_domain(idx)

    def __call__(self, idx=0):
        return self._get_domain(idx)

    def __getattr__(self, name):
        return getattr(self._get_domain(0), name)

    def __repr__(self):
        return repr(self._get_domain(0))
     

class AxisAccessor:
    def __init__(self, field_id):
        self.field_id = field_id

    def _get_axis(self, idx):
        full_id = f"{self.field_id}::[{idx}]"
        if is_valid_axis(full_id):
            return Axis(full_id)
        return None
        

    def __getitem__(self, idx):
        return self._get_axis(idx)

    def __call__(self, idx=0):
        return self._get_axis(idx)

    def __getattr__(self, name):
        return getattr(self._get_axis(0), name)

    def __repr__(self):
        return repr(self._get_axis(0))