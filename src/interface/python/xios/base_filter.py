from xios import Domain
from xios import Axis
from xios import Context

class Filter:


    def __init__(self, context_id, field_ids=None, argin_ids=None):
        print("context_id is ", context_id)
        self.ctx = Context(context_id, is_service=True)
        self._mapping_id = dict(zip(argin_ids, field_ids))

        for argin_id in self._mapping_id:
            setattr(self, argin_id, self.ctx.field(self._mapping_id[argin_id]))

        self._initialized = False


    def _framework_initialize(self):
        """Called by C++ after instantiation"""
        self._initialized = True
        return self.initialize()

    def _framework_process(self, *arrays):
        """Called by C++ at each timestep"""
        for argin_id, array in zip(self._mapping_id, arrays):
            field = getattr(self, argin_id)
            field._set_data(array)
        self.current_date = self.ctx.calendar.current_date
        if not self._initialized:
            raise RuntimeError("Filter not initialized")
        return self.apply()

    # User can override
    def initialize(self):
        pass

    # User must override
    def apply(self, *arrays):
        raise NotImplementedError
