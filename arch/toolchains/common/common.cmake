# ---------------------------------------------------------------------------
# Common helper macros for all toolchain files
# ---------------------------------------------------------------------------

macro(set_flags var value)
    set(${var} "${value}" CACHE STRING "" FORCE)
endmacro()

macro(add_flags var value)
    string(APPEND ${var} " ${value}")
endmacro()
