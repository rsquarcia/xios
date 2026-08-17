from xios.odata import _xios_instance
from xios.idata import context_initialize, close_context_definition, context_finalize, context_is_initialized, getVar
from xios.ocalendar import Calendar
from xios.obj import swipswap_ctx
from xios.config import String, Double, Bool, Int
from xios.ocontext_attr import Context_
from xios.icontext import set_current_context, set_current_context_id, is_valid_context

from xios.oscalar_attr import Scalar
from xios.oscalargroup_attr import ScalarGroup
from xios.oaxis_attr import Axis
from xios.oaxisgroup_attr import AxisGroup
from xios.odomain_attr import Domain
from xios.odomaingroup_attr import DomainGroup
from xios.ogrid_attr import Grid
from xios.ogridgroup_attr import GridGroup
from xios.ofield import Field
from xios.ofieldgroup_attr import FieldGroup
from xios.ovariable import Variable
from xios.ovariablegroup_attr import VariableGroup
from xios.ofile_attr import File
from xios.ofilegroup_attr import FileGroup
from xios.ofunction_attr import Function
from xios.ofunctiongroup_attr import FunctionGroup

from xios.ozoom_domain_attr import ZoomDomain
from xios.oextract_domain_attr import ExtractDomain
from xios.ointerpolate_domain_attr import InterpolateDomain
from xios.ogenerate_rectilinear_domain_attr import GenerateRectilinearDomain
from xios.ocompute_connectivity_domain_attr import ComputeConnectivityDomain
from xios.oexpand_domain_attr import ExpandDomain
from xios.oreorder_domain_attr import ReorderDomain
from xios.oredistribute_domain_attr import RedistributeDomain

from xios.ozoom_axis_attr import ZoomAxis
from xios.ointerpolate_axis_attr import InterpolateAxis
from xios.oinverse_axis_attr import InverseAxis
from xios.oreduce_domain_to_axis_attr import ReduceDomainToAxis
from xios.oreduce_axis_to_axis_attr import ReduceAxisToAxis
from xios.oextract_domain_to_axis_attr import ExtractDomainToAxis
from xios.otemporal_splitting_attr import TemporalSplitting
from xios.oduplicate_scalar_to_axis_attr import DuplicateScalarToAxis
from xios.oredistribute_axis_attr import RedistributeAxis

from xios.oreduce_axis_to_scalar_attr import ReduceAxisToScalar
from xios.oextract_axis_to_scalar_attr import ExtractAxisToScalar
from xios.oreduce_domain_to_scalar_attr import ReduceDomainToScalar
from xios.oreduce_scalar_to_scalar_attr import ReduceScalarToScalar
from xios.oredistribute_scalar_attr import RedistributeScalar


class Context(Context_):

    def __init__(self, context_id, comm = None, is_service = False):
        super().__init__(id = context_id)

        if not context_is_initialized(context_id) and not is_service:
            if comm is None :                
                comm = _xios_instance._communicator
            context_initialize(context_id, comm)

        self._initialized = True
        self._finalized   = False
        self._closed      = False

        self._context_id = context_id
        set_current_context(String(context_id))
        self._calendar = Calendar()
    
    @property
    def calendar(self):
        return self._calendar


    def close_definition(self):
        if not self._calendar._is_defined : raise RuntimeError("Cannot close definition without defining the calendar !")
        if self._finalized : raise RuntimeError("Cannot use context after it has been finalized.")
        if self._closed : raise RuntimeError("Context already closed !")
        self._closed = True
        current_context_id = swipswap_ctx(self._id)
        close_context_definition()
        swipswap_ctx(current_context_id)

    def finalize(self):
        if self._finalized : raise RuntimeError("Cannot use context after it has been finalized.")
        current_context_id = swipswap_ctx(self._id)
        context_finalize()
        self._finalized = True
        if current_context_id.value != self._id.value:
            set_current_context_id(String(current_context_id))
        


    @property
    def initialized(self):
        self._initialized = context_is_initialized(self._id)
        return self._initialized

    @property
    def finalized(self):
        return self._finalized
    
    def __str__(self):
        return str(self._id)

    def set_current(self):
        set_current_context(String(self._id))

    def getvar(self, id, data = 0):
        if isinstance(data, float):
            data_c = Double(data)
        elif isinstance(data, bool):
            data_c = Bool(data)
        elif isinstance(data, int):
            data_c = Int(data)
        elif isinstance(data, str):
            data_c = String()

        current_context_id = swipswap_ctx(self._id)
        is_valid = getVar(id, data_c)
        swipswap_ctx(current_context_id)
        if is_valid :
            return data_c.value
        else :
            return None

    
def dynamic_methods():
    CLASS_MAP = {
    "scalar": Scalar, "scalargroup": ScalarGroup,
    "axis": Axis, "axisgroup": AxisGroup, 
    "domain": Domain, "domaingroup": DomainGroup,
    "grid": Grid, "gridgroup": GridGroup,
    "field": Field, "fieldgroup": FieldGroup,
    "variable": Variable, "variablegroup": VariableGroup,
    "file": File, "filegroup": FileGroup,
    "function": Function, "functiongroup": FunctionGroup,

    "zoom_domain" : ZoomDomain, "extract_domain": ExtractDomain,
    "interpolate_domain": InterpolateDomain,
    "generate_rectilinear_domain": GenerateRectilinearDomain,
    "compute_connectivity_domain": ComputeConnectivityDomain,
    "expand_domain": ExpandDomain, "reorder_domain": ReorderDomain, 
    "redistribute_domain": RedistributeDomain,

    "zoom_axis": ZoomAxis, "interpolate_axis": InterpolateAxis, 
    "inverse_axis": InverseAxis, "reduce_domain_to_axis": ReduceDomainToAxis,
    "reduce_axis_to_axis" : ReduceAxisToAxis,
    "extract_domain_to_axis": ExtractDomainToAxis,
    "temporal_splitting": TemporalSplitting,
    "duplicate_scalar_to_axis": DuplicateScalarToAxis,
    "redistribute_axis": RedistributeAxis,

    "reduce_axis_to_scalar" : ReduceAxisToScalar, 
    "extract_axis_to_scalar" : ExtractAxisToScalar,
    "reduce_domain_to_scalar": ReduceDomainToScalar,
    "reduce_scalar_to_scalar": ReduceScalarToScalar,
    "redistribute_scalar": RedistributeScalar
    }

    def create_method(name):
        def method(self, id, **kwargs):
            current_context_id = swipswap_ctx(self._id)
            cls = CLASS_MAP[name]
            is_valid_func = self._resolve_func(f"is_valid_{name}", f"xios.i{name}")
            if is_valid_func(String(id)):
                res = cls(id)
            else : 
                return None
            for key, value in kwargs.items():
                if key in cls.FIELD_META:
                    setattr(cls, key, value)
                else:
                    raise AttributeError(f"Unknown attribute '{key}' for class '{cls._object_type}'")
            swipswap_ctx(current_context_id)
            return res
        return method

    def create_is_valid(name):
        def is_valid(self, id):
            current_context_id = swipswap_ctx(self._id)
            is_valid_func = self._resolve_func(f"is_valid_{name}", f"xios.i{name}")
            res = is_valid_func(String(id))
            swipswap_ctx(current_context_id)
            return res
        return is_valid

    for key in CLASS_MAP:
        setattr(Context, f'{key}', create_method(key))
        setattr(Context, f'is_valid_{key}', create_is_valid(key))
        

dynamic_methods()