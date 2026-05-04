from xios.ovariable_attr import Variable_
from xios.idata import getVar, receive_field
from xios.obj import swipswap_ctx
from xios.config import Bool, Double, Int, NpArray, String


class Variable(Variable_):

    def __init__(self, id : str = None):
        super().__init__(id)

    def get(self, data):
        if isinstance(data, float):
            data = Double(data)
        elif isinstance(data, int):
            data = Int(data)
        elif isinstance(data, bool):
            data = Bool(data)
        elif isinstance(data, str):
            data = String()
        
        current_context_id = swipswap_ctx(self._context_id)
        if getVar(self.id, data):
            swipswap_ctx(current_context_id)
            return data.value
        swipswap_ctx(current_context_id)

    def receive(self, data):
        current_context_id = swipswap_ctx(self._context_id)
        data = NpArray(data)
        receive_field(self._id, data)
        swipswap_ctx(current_context_id)
        return data.arr