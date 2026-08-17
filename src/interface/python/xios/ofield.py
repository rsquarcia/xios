from xios.ofield_attr import Field_
from xios.idata import send_field, receive_field
from xios.config import NpArray
from xios.obj import swipswap_ctx
from xios.oaxis_attr import Axis
from xios.odomain_attr import Domain
from xios.oscalar_attr import Scalar
from xios.ifield import field_is_active, field_get_axis, field_get_domain, field_get_scalar
from xios.ifield import field_get_domains_number, field_get_axes_number, field_get_scalars_number
import numpy as np

class Field(Field_):

    def __init__(self, id : str = None):
        super().__init__(id)
        self._data = None
        self._shape = None
        self._axis_hdl = None
        self._scalar_hdl = None
        self._domain_hdl = None

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
    
    def is_active(self, at_current_time_step = False) :
        return field_is_active(self._id, at_current_time_step)
    
    def _set_data(self, data):
        self._data = data

    @property
    def axis(self):
        return self.axes[0]
    
    @property
    def axes(self):
        return AxisAccessor(self, self._id)
    
    @property
    def domain(self):
        return self.domains[0]

    @property
    def domains(self):
        return DomainAccessor(self, self._id)
    
    @property
    def scalar(self):
        return self.scalars[0]

    @property
    def scalars(self):
        return ScalarAccessor(self, self._id)
    
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

        curr = self.domains[0]
        j = 0
        while curr is not None:
            shape.append(self.domains[j].nj)
            shape.append(self.domains[j].ni)
            j=j+1
            curr = self.domains[j]

        self._shape = tuple(shape)
        return self._shape
            

    

class DomainAccessor:
    def __init__(self, field_hdl, field_id):
        self._field_hdl = field_hdl
        self.field_id = field_id
        self._domains_number = field_get_domains_number(field_id)

    def _get_domain(self, idx):
        if idx >= self._domains_number : return None
        self._domain_hdl = Domain()
        field_get_domain(self._field_hdl, self._domain_hdl, idx)
        self._domain_hdl._module_name_attr = f"xios.idomain_attr"
        self._domain_hdl._class_name = "domain"
        self._domain_hdl._id = f"{self.field_id}::[{idx}]"
        return self._domain_hdl

    def __getitem__(self, idx):
        return self._get_domain(idx)

    def __call__(self, idx=0):
        return self._get_domain(idx)

    def __getattr__(self, name):
        return getattr(self._get_domain(0), name)

    def __repr__(self):
        return repr(self._get_domain(0))
     

class AxisAccessor:
    def __init__(self, field_hdl, field_id):
        self._field_hdl = field_hdl
        self.field_id = field_id
        self._axes_number = field_get_axes_number(field_id)

    def _get_axis(self, idx):
        if idx >= self._axes_number : return None
        self._axis_hdl = Axis()
        field_get_axis(self._field_hdl, self._axis_hdl, idx)
        self._axis_hdl._module_name_attr = f"xios.iaxis_attr"
        self._axis_hdl._class_name = "axis"
        self._axis_hdl._id = f"{self.field_id}::[{idx}]"
        return self._axis_hdl
        

    def __getitem__(self, idx):
        return self._get_axis(idx)

    def __call__(self, idx=0):
        return self._get_axis(idx)

    def __getattr__(self, name):
        return getattr(self._get_axis(0), name)

    def __repr__(self):
        return repr(self._get_axis(0))
    
class ScalarAccessor:
    def __init__(self, field_hdl, field_id):
        self._field_hdl = field_hdl
        self.field_id = field_id
        self._scalars_number = field_get_scalars_number(field_id)

    def _get_scalar(self, idx):
        if idx >= self._scalars_number : return None
        self._scalar_hdl = Scalar()
        field_get_scalar(self._field_hdl, self._scalar_hdl, idx)
        self._scalar_hdl._module_name_attr = f"xios.iscalar_attr"
        self._scalar_hdl._class_name = "scalar"
        self._scalar_hdl._id = f"{self.field_id}::[{idx}]"
        return self._scalar_hdl
        

    def __getitem__(self, idx):
        return self._get_scalar(idx)

    def __call__(self, idx=0):
        return self._get_scalar(idx)

    def __getattr__(self, name):
        return getattr(self._get_scalar(0), name)

    def __repr__(self):
        return repr(self._get_scalar(0))