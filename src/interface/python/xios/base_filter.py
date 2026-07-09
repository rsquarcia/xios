from xios.ocontext import Context


class Filter:
    def __init__(self, context_id, field_ids=None, scalar_ids=None, argin_ids=None):
        self.ctx = Context(context_id, is_service=True)
        self._mapping_id = {}

        for idx, argin_id in enumerate(argin_ids):
            field_id = field_ids.get(idx)
            scalar_id = scalar_ids.get(idx)
            if field_id is not None:
                self._mapping_id[argin_id] = (field_id, "field")
            else:
                self._mapping_id[argin_id] = (scalar_id, "var")

        # Create attributes for each input field
        for argin_id, (id, kind) in self._mapping_id.items():
            if kind == "field":
                setattr(self, argin_id, self.ctx.field(id))
            else:
                setattr(self, argin_id, self.ctx.variable(id))

            self._initialized = False

    def _framework_initialize(self):
        """Called by C++ after instantiation"""
        self._initialized = True
        return self.initialize()

    def _framework_process(self, *arrays):
        """Called by C++ at each timestep"""

        # Assign incoming arrays to corresponding fields
        arrays_iter = iter(arrays)

        for (argin_id, (_,kind)) in self._mapping_id.items():
            if kind == "field":
                field = getattr(self, argin_id)
                field._set_data(next(arrays_iter))

            
        self.current_date = self.ctx.calendar.current_date

        if not self._initialized:
            raise RuntimeError("Filter not initialized")

        return self.apply()

    # Optional override
    def initialize(self):
        pass

    # Mandatory override
    def apply(self):
        raise NotImplementedError("Filter subclasses must implement apply()")