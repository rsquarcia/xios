# FindPython.cmake
# Finds the Python C API (Python.h) and the NumPy C API (numpy/arrayobject.h)
# headers, plus the Python library, for the optional XIOS Python bindings.
# NumPy is folded into this module rather than given its own Find module,
# since it only ever contributes a header search path.
#
# ============================================================
# RESULT VARIABLES
# ============================================================
#
#   Python_FOUND             - True if all of the below were found.
#   Python_INCLUDE_DIR       - Directory containing Python.h.
#   Python_NumPy_INCLUDE_DIR - Directory containing numpy/arrayobject.h.
#   Python_LIBRARY           - The Python library.
#
# ============================================================
# IMPORTED TARGETS
# ============================================================
#
#   Python::Python — Python library with both include dirs (Python + NumPy).
#
# Usage in CMakeLists.txt:
#   find_package(Python REQUIRED)
#   target_link_libraries(xios PRIVATE Python::Python)
#
# ============================================================

include(${CMAKE_CURRENT_LIST_DIR}/helpers.cmake)

if(TARGET Python::Python)
    return()
endif()

# ---------------------------------------------------------------------------
# Collect path hints from environment variables
# ---------------------------------------------------------------------------

set(_python_inc_hints "")
set(_python_lib_hints "")
set(_numpy_inc_hints "")

# Root path
foreach(_root_var PYTHON_ROOT Python_ROOT PYTHON_DIR)
    if(NOT "$ENV{${_root_var}}" STREQUAL "")
        list(APPEND _python_inc_hints "$ENV{${_root_var}}/include")
        list(APPEND _python_lib_hints "$ENV{${_root_var}}/lib"
                                      "$ENV{${_root_var}}/lib64")
    endif()
endforeach()

# Include path (Python)
foreach(_inc_var PYTHON_INCDIR PYTHON_INC_DIR)
    if(NOT "$ENV{${_inc_var}}" STREQUAL "")
        list(APPEND _python_inc_hints "$ENV{${_inc_var}}")
    endif()
endforeach()

# Library path (Python)
foreach(_lib_var PYTHON_LIBDIR PYTHON_LIB_DIR)
    if(NOT "$ENV{${_lib_var}}" STREQUAL "")
        list(APPEND _python_lib_hints "$ENV{${_lib_var}}")
    endif()
endforeach()

# Include path (NumPy)
foreach(_inc_var NUMPY_INCDIR NUMPY_INC_DIR)
    if(NOT "$ENV{${_inc_var}}" STREQUAL "")
        list(APPEND _numpy_inc_hints "$ENV{${_inc_var}}")
    endif()
endforeach()

# ---------------------------------------------------------------------------
# Locate headers and library
# ---------------------------------------------------------------------------

find_path(Python_INCLUDE_DIR
    NAMES Python.h
    HINTS ${_python_inc_hints}
    PATH_SUFFIXES include
)

find_path(Python_NumPy_INCLUDE_DIR
    NAMES numpy/arrayobject.h
    HINTS ${_numpy_inc_hints}
    PATH_SUFFIXES include
)

# The library is essentially always installed under its versioned name
# (libpython3.N.so); an unversioned libpython3.so is not guaranteed.
set(_python_lib_names python3)
foreach(_v RANGE 13 6 -1)
    list(APPEND _python_lib_names python3.${_v})
endforeach()

find_library(Python_LIBRARY
    NAMES ${_python_lib_names}
    HINTS ${_python_lib_hints}
    PATH_SUFFIXES lib lib64
)

# ---------------------------------------------------------------------------
# Check that all components were found
# ---------------------------------------------------------------------------

check_required_args(Python
    REQUIRED_VARS
        Python_LIBRARY
        Python_INCLUDE_DIR
        Python_NumPy_INCLUDE_DIR
    FAIL_MESSAGE
        "Python (with NumPy headers) not found. Set one of the following:"
        "  - PYTHON_ROOT (root of the Python installation, e.g. a venv or conda env)"
        "  - PYTHON_INCDIR + PYTHON_LIBDIR (Python.h + library, split paths)"
        "  - NUMPY_INCDIR (directory containing numpy/arrayobject.h)"
)

if(NOT Python_FOUND)
    return()
endif()

# ---------------------------------------------------------------------------
# Create the IMPORTED target
# ---------------------------------------------------------------------------

if(NOT TARGET Python::Python)
    add_library(Python::Python INTERFACE IMPORTED)
    set_target_properties(Python::Python PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${Python_INCLUDE_DIR};${Python_NumPy_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES      "${Python_LIBRARY}"
    )
endif()
