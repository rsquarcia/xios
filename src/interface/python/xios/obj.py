import functools
from xios.config import String, CObject, Bool, convert_type
import importlib
from xios.icontext import get_current_context_id, set_current_context_id
import numpy as np
import inspect



def swipswap_ctx(tmp_context_id):
    current_context_id = String()
    get_current_context_id(current_context_id)
    set_current_context_id(String(tmp_context_id))
    return current_context_id


def current_context_id():
    current_context_id = String()
    get_current_context_id(current_context_id)
    return current_context_id.value



#####################################################################################################
##                              Object-oriented super class                                        ##
#####################################################################################################


class Object(CObject):
    FIELD_META = {}
    _is_methods_generated = False

    def __init__(self, id = None):
        if id is None : return
        self._is_methods_generated = False
        self._module_name_attr =  f"xios.i{self._object_type.lower()}_attr"
        self._class_name = ''.join(word.title() for word in self._object_type.split('_'))
        if self._object_type.lower() in ['context', 'variable', 'field']:
            self._omodule_name =  f"xios.o{self._object_type.lower()}"
        else:
            self._omodule_name =  f"xios.o{self._object_type.lower()}_attr"
        self._module_name  = f'xios.i{self._object_type.lower()[:-5] if self._object_type.lower().endswith("group") else self._object_type.lower()}'

        self._id = String(id)
        get_hdl_func = self._resolve_func(f"get_{self._object_type}_handle", self._module_name)
        get_hdl_func(self._id, self)

        cls = self.__class__
        if not cls._is_methods_generated:
            cls._generate_child_methods()
            cls._generate_is_defined_methods()
            cls._is_methods_generated = True


    def _resolve_func(self, func_name: str, module: str):
        mod = importlib.import_module(module)
        try:
            return getattr(mod, func_name)
        except AttributeError:
            raise RuntimeError(f"Function '{func_name}' not found in module '{mod.__name__}'")

    def __getattr__(self, name: str):

        cls_attr = getattr(type(self), name, None)
        if callable(cls_attr):
            return functools.partial(cls_attr, self)

        if name.startswith("_") or name not in self.FIELD_META:
            raise AttributeError(f"'{type(self).__name__}' object has no attribute '{name}'")


        is_defined_func = self._resolve_func(f"is_defined_{self._object_type}_attr_hdl", self._module_name_attr)
        is_defined = Bool(False)
        is_defined_func(self, **{name: is_defined})
        if not is_defined.value:
            return None

        meta = self.FIELD_META[name]
        WrappedType = convert_type(meta)
        wrapper = WrappedType() if "ndim" in meta else WrappedType()

        getter_func = self._resolve_func(f"get_{self._object_type}_attr_hdl", self._module_name_attr)
        current_context_id = swipswap_ctx(self._context_id)
        getter_func(self, **{name: wrapper})
        swipswap_ctx(current_context_id)
        return wrapper.value


    def __setattr__(self, name: str, value):
        if name.startswith("_"):
            object.__setattr__(self, name, value)
            return

        cls_attr = getattr(type(self), name, None)
        if isinstance(cls_attr, property) and cls_attr.fset is not None:
            cls_attr.fset(self, value)
            return


        if name not in self.FIELD_META:
            raise AttributeError(f"No such attribute: {name}")

        meta = self.FIELD_META[name]
        WrappedType = convert_type(meta)

        if isinstance(value, np.ndarray) and "ndim" in meta:
            if value.ndim != meta["ndim"]:
                raise ValueError(f"{name} must be a {meta['ndim']}D NumPy array")

        wrapped_value = WrappedType(value)
        setter_func = self._resolve_func(f"set_{self._object_type}_attr_hdl", self._module_name_attr)
        current_context_id = swipswap_ctx(self._context_id)
        setter_func(self, **{name: wrapped_value})
        swipswap_ctx(current_context_id)


    @classmethod
    def _generate_child_methods(cls):
        tree_module_name  = f"xios.ixml_tree"
        tree_module = importlib.import_module(tree_module_name)
        functions = inspect.getmembers(tree_module, inspect.isfunction)
        imported_classes = [
            name for name, obj in inspect.getmembers(tree_module, inspect.isclass)
            if obj.__module__ != tree_module.__name__
        ]
        build_functions = {}
        for function in functions:
            if function[0][:4] == "add_":
                s = function[0][4:]
                if "to" in s:
                    child, parent = s.split("to", 1)
                else:
                    child, parent = s, ""
                if parent == "":
                    if "redistribute" not in child:
                        if 'group' not in child : parent = child+"group"
                        else : parent = child
                    elif "redistribute" in child:
                        parent = child[12:]
                    else :
                        raise ValueError(f"add_element function not valid for child : {child} and parent {parent}")
                if cls._object_type == parent :
                    build_functions.setdefault(child, []).append((parent, function[1]))

        
        for child in build_functions:     
            def make_method(child=child):
                def method(self, child_id = None):
                    parent_hdl = self
                    child_class_name = next((s for s in imported_classes if s.lower() == child), None)
                    child_class = cls._resolve_func(cls, child_class_name, f"xios")
                    child_hdl    = child_class()
                    for parent, function in build_functions[child]:
                        parent_class_name = next((s for s in imported_classes if s.lower() == parent), None)
                        parent_type = cls._resolve_func(cls, parent_class_name, f"xios.o{parent}_attr")
                        if isinstance(parent_hdl, parent_type):
                            function(parent_hdl, child_hdl, child_id)
                    child_hdl._module_name_attr = f"xios.i{child_class_name.lower()}_attr"
                    child_hdl._class_name = child_class_name
                    child_hdl._id = String(child_id) if child_id else "__undefined_id__"
                    return child_hdl
                return method
            
            setattr(cls, f"add_{child}", make_method(child))

    @classmethod
    def _generate_is_defined_methods(cls):
        for attr in cls.FIELD_META:
            def make_method(attr):
                def method(self):
                    is_defined_func = self._resolve_func(f"is_defined_{cls._object_type}_attr", f"xios.i{cls._object_type}_attr")
                    is_defined_res = Bool(False)
                    is_defined_func(String(self._id), **{attr: is_defined_res})
                    return is_defined_res.value
                return method

            setattr(cls, f"is_defined_{attr}", make_method(attr))

    def __str__(self):
        s = ""
        s += f"{self._class_name} '{self.id}' "
        s += f"in context '{self._context_id}'\n"
        for k in self.FIELD_META:
            if k != f'{self._object_type}_id':
                value = getattr(self, k, None)
                if value is not None:
                    s += f"  {k} = {value}\n"
        return s
    
    def set_attr(self, **kwargs):
        current_context_id = swipswap_ctx(self._context_id)
        for key, value in kwargs.items():
            if key in self.FIELD_META:
                setattr(self, key, value)
            else:
                raise AttributeError(f'Unknown attribute {key} for class {self.__class__.__name__}')
        swipswap_ctx(current_context_id)
    
    def get_attr(self):
        attr_dict = {}
        current_context_id = swipswap_ctx(self._context_id)
        for attr in self.FIELD_META :
            if attr != f'{self._object_type}_id':
                value = getattr(self, attr, None)
                attr_dict[attr] = value
        swipswap_ctx(current_context_id)
        return attr_dict

    @property
    def id(self):
        return self._id
    
    @property
    def context_id(self):
        return self._context_id
        
    @classmethod
    def help(cls):
        print(f"\nHelp for {cls.__name__}")
        print("-" * 60)
        for attr, meta in cls.FIELD_META.items():
            attr_type = meta.get('type', 'Unknown')
            if attr_type is np.ndarray:  # <-- compare to actual type, not string
                array_type = meta.get('array_type', 'Unknown')
                ndim = meta.get('ndim', None)
                array_type_name = (
                    array_type.__name__ if hasattr(array_type, '__name__') else str(array_type)
                )
                ndim_str = f", {ndim}" if ndim is not None else ""
                type_str = f"numpy.ndarray[{array_type_name}{ndim_str}]"
            else:
                type_str = (
                    attr_type.__name__ if hasattr(attr_type, '__name__') else str(attr_type)
                )
            print(f"{attr:<25} : {type_str}")
        print("-" * 60)

