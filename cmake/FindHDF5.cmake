# FindHDF5.cmake
# Finds the HDF5 C library.
#
# ============================================================
# RESULT VARIABLES
# ============================================================
#
#   HDF5_FOUND       - True if the library was found.
#   HDF5_INCLUDE_DIR - The directory where hdf5.h is found.
#   HDF5_C_LIBRARY   - The HDF5 C library.
#   HDF5_HL_LIBRARY  - The HDF5 High-Level library.
#
# ============================================================
# IMPORTED TARGETS
# ============================================================
#
#   HDF5::C         — bundles hdf5_hl + hdf5 + zlib with include dir.
#
# Usage in CMakeLists.txt:
#   find_package(HDF5 REQUIRED)
#   target_link_libraries(xios PRIVATE HDF5::C)
#
# ============================================================

include(${CMAKE_CURRENT_LIST_DIR}/helpers.cmake)

if(TARGET HDF5::C)
    return()
endif()

# ---------------------------------------------------------------------------
# Collect path hints from environment variables
# ---------------------------------------------------------------------------

set(_hdf5_inc_hints "")
set(_hdf5_lib_hints "")

# Root path
foreach(_root_var HDF5_ROOT Hdf5_ROOT HDF5_DIR)
    if(NOT "$ENV{${_root_var}}" STREQUAL "")
        list(APPEND _hdf5_inc_hints "$ENV{${_root_var}}/include")
        list(APPEND _hdf5_lib_hints "$ENV{${_root_var}}/lib"
                                    "$ENV{${_root_var}}/lib64")
    endif()
endforeach()

# Include path
foreach(_inc_var HDF5_INC_DIR HDF5_INCDIR)
    if(NOT "$ENV{${_inc_var}}" STREQUAL "")
        list(APPEND _hdf5_inc_hints "$ENV{${_inc_var}}")
    endif()
endforeach()

# Library path
foreach(_lib_var HDF5_LIB_DIR HDF5_LIBDIR)
    if(NOT "$ENV{${_lib_var}}" STREQUAL "")
        list(APPEND _hdf5_lib_hints "$ENV{${_lib_var}}")
    endif()
endforeach()

# ---------------------------------------------------------------------------
# Locate header and libraries
# ---------------------------------------------------------------------------

find_path(HDF5_INCLUDE_DIR
    NAMES hdf5.h
    HINTS ${_hdf5_inc_hints}
    PATH_SUFFIXES hdf5 hdf5/serial hdf5/parallel include
)

find_library(HDF5_C_LIBRARY
    NAMES hdf5
    HINTS ${_hdf5_lib_hints}
    PATH_SUFFIXES lib lib64 hdf5/lib hdf5/lib64
)

find_library(HDF5_HL_LIBRARY
    NAMES hdf5_hl
    HINTS ${_hdf5_lib_hints}
    PATH_SUFFIXES lib lib64 hdf5/lib hdf5/lib64
)

# ---------------------------------------------------------------------------
# Check that all components were found
# ---------------------------------------------------------------------------

check_required_args(HDF5
    REQUIRED_VARS
        HDF5_C_LIBRARY
        HDF5_HL_LIBRARY
        HDF5_INCLUDE_DIR
    FAIL_MESSAGE
        "HDF5 not found. Set one of the following:"
        "  - HDF5_DIR, HDF5_ROOT (unified root)"
        "  - HDF5_INC_DIR + HDF5_LIB_DIR (split unified, colon-separated paths accepted)"
)

if(NOT HDF5_FOUND)
    return()
endif()

# ---------------------------------------------------------------------------
# Create the IMPORTED target
# ---------------------------------------------------------------------------

if(NOT TARGET HDF5::C)
    add_library(HDF5::C INTERFACE IMPORTED)
    set_target_properties(HDF5::C PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${HDF5_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES      "${HDF5_HL_LIBRARY};${HDF5_C_LIBRARY}"
    )
    # Zlib is required by HDF5
    find_package(ZLIB QUIET)
    if(ZLIB_FOUND)
        target_link_libraries(HDF5::C INTERFACE ZLIB::ZLIB)
    else()
        target_link_libraries(HDF5::C INTERFACE z)
    endif()
endif()
