from xios.ovariable_attr import Variable_
from xios.idata import getVar, receive_field
from xios.obj import swipswap_ctx
from xios.config import Bool, Double, Int, NpArray, String


class Variable(Variable_):

    def __init__(self, id : str = None):
        super().__init__(id)
        self._data = None

    @property
    def value(self, data = 0):
        if isinstance(data, float):
            data_c = Double(data)
        elif isinstance(data, int):
            data_c = Int(data)
        elif isinstance(data, bool):
            data_c = Bool(data)
        elif isinstance(data, str):
            data_c = String()
        
        current_context_id = swipswap_ctx(self._context_id)
        is_valid = getVar(self._id, data_c)
        swipswap_ctx(current_context_id)
        if is_valid :
            return data_c.value
        else : 
            return None

    def receive(self, data):
        current_context_id = swipswap_ctx(self._context_id)
        data = NpArray(data)
        receive_field(self._id, data)
        swipswap_ctx(current_context_id)
        return data.arr