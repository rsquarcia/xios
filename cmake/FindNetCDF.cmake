# FindNetCDF.cmake
# Finds the NetCDF-C and NetCDF-Fortran libraries.
#
# ============================================================
# COMPONENTS
# ============================================================
#
#   C       - Find NetCDF-C (default if no components specified)
#   Fortran - Find NetCDF-Fortran (implies C)
#
# ============================================================
# RESULT VARIABLES
# ============================================================
#
#   NetCDF_FOUND               - True if all requested components were found.
#   NetCDF_C_INCLUDE_DIR       - Directory containing netcdf.h.
#   NetCDF_C_LIBRARY           - The NetCDF-C library.
#   NetCDF_Fortran_INCLUDE_DIR - Directory containing netcdf.mod.
#   NetCDF_Fortran_LIBRARY     - The NetCDF-Fortran library.
#
# ============================================================
# IMPORTED TARGETS
# ============================================================
#
#   NetCDF::C       — NetCDF-C library with include dir.
#   NetCDF::Fortran — NetCDF-Fortran library with include dir; links NetCDF::C.
#
# ============================================================

include(${CMAKE_CURRENT_LIST_DIR}/helpers.cmake)

# Default to C if no components requested
if(NOT NetCDF_FIND_COMPONENTS)
    set(NetCDF_FIND_COMPONENTS C)
endif()

# NetCDF::Fortran always depends on NetCDF::C
if("Fortran" IN_LIST NetCDF_FIND_COMPONENTS AND NOT "C" IN_LIST NetCDF_FIND_COMPONENTS)
    list(APPEND NetCDF_FIND_COMPONENTS C)
endif()

# Early exit if all requested component targets already exist
set(_netcdf_all_found TRUE)
foreach(_comp IN LISTS NetCDF_FIND_COMPONENTS)
    if(NOT TARGET NetCDF::${_comp})
        set(_netcdf_all_found FALSE)
        break()
    endif()
endforeach()
if(_netcdf_all_found)
    return()
endif()

# ---------------------------------------------------------------------------
# Collect path hints from environment variables
# ---------------------------------------------------------------------------

set(_nc_inc_hints "")
set(_nc_lib_hints "")
set(_ncf_inc_hints "")
set(_ncf_lib_hints "")

# Root path (C and Fortran)
foreach(_root_var NETCDF_DIR NETCDF4_DIR NETCDF_ROOT NetCDF_ROOT NETCDF_C_ROOT NETCDF_FORTRAN_ROOT)
    if(NOT "$ENV{${_root_var}}" STREQUAL "")
        list(APPEND _nc_inc_hints  "$ENV{${_root_var}}/include")
        list(APPEND _ncf_inc_hints "$ENV{${_root_var}}/include")
        list(APPEND _nc_lib_hints  "$ENV{${_root_var}}/lib"
                                   "$ENV{${_root_var}}/lib64")
        list(APPEND _ncf_lib_hints "$ENV{${_root_var}}/lib"
                                   "$ENV{${_root_var}}/lib64")
    endif()
endforeach()

# Include path (C and Fortran)
_split_colon(NETCDF_INC_DIR _split)
list(APPEND _nc_inc_hints  ${_split})
list(APPEND _ncf_inc_hints ${_split})

_split_colon(NETCDF_LIB_DIR _split)
list(APPEND _nc_lib_hints  ${_split})
list(APPEND _ncf_lib_hints ${_split})

# Include path (C only)
foreach(_var NETCDFC_INCDIR NETCDFC_INC_DIR)
    if(NOT "$ENV{${_var}}" STREQUAL "")
        list(APPEND _nc_inc_hints "$ENV{${_var}}")
    endif()
endforeach()

# Library path (C only)
foreach(_var NETCDFC_LIBDIR NETCDFC_LIB_DIR)
    if(NOT "$ENV{${_var}}" STREQUAL "")
        list(APPEND _nc_lib_hints "$ENV{${_var}}")
    endif()
endforeach()

# Include path (Fortran only)
foreach(_var NETCDFFORTRAN_INCDIR NETCDFFORTRAN_INC_DIR)
    if(NOT "$ENV{${_var}}" STREQUAL "")
        list(APPEND _ncf_inc_hints "$ENV{${_var}}")
    endif()
endforeach()

# Library path (Fortran only)
foreach(_var NETCDFFORTRAN_LIBDIR NETCDFFORTRAN_LIB_DIR)
    if(NOT "$ENV{${_var}}" STREQUAL "")
        list(APPEND _ncf_lib_hints "$ENV{${_var}}")
    endif()
endforeach()

# ---------------------------------------------------------------------------
# Locate C header and library
# ---------------------------------------------------------------------------

if("C" IN_LIST NetCDF_FIND_COMPONENTS AND NOT TARGET NetCDF::C)
    find_path(NetCDF_C_INCLUDE_DIR
        NAMES netcdf.h
        HINTS ${_nc_inc_hints}
        PATH_SUFFIXES include
    )

    find_library(NetCDF_C_LIBRARY
        NAMES netcdf
        HINTS ${_nc_lib_hints}
        PATH_SUFFIXES lib lib64
    )

    check_required_args(NetCDF-C
        NAME_MISMATCHED
        REQUIRED_VARS
            NetCDF_C_LIBRARY
            NetCDF_C_INCLUDE_DIR
        FAIL_MESSAGE
            "NetCDF-C not found. Set one of the following:"
            "  - NETCDF_DIR, NETCDF4_DIR, or NETCDF_C_ROOT (unified root)"
            "  - NETCDF_INC_DIR + NETCDF_LIB_DIR (split unified, colon-separated paths accepted)"
            "  - NETCDFC_INCDIR + NETCDFC_LIBDIR (C-specific)"
    )

    if(NOT NetCDF_FOUND)
        return()
    endif()

    add_library(NetCDF::C INTERFACE IMPORTED)
    set_target_properties(NetCDF::C PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${NetCDF_C_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES      "${NetCDF_C_LIBRARY}"
    )

    # libnetcdf with parallel HDF5 support
    find_package(HDF5 QUIET)
    if(HDF5_FOUND)
        target_link_libraries(NetCDF::C INTERFACE HDF5::C)
    endif()
endif()

# ---------------------------------------------------------------------------
# Locate Fortran module and library
# ---------------------------------------------------------------------------

if("Fortran" IN_LIST NetCDF_FIND_COMPONENTS AND NOT TARGET NetCDF::Fortran)
    find_path(NetCDF_Fortran_INCLUDE_DIR
        NAMES netcdf.mod
        HINTS ${_ncf_inc_hints}
        PATH_SUFFIXES include
    )

    find_library(NetCDF_Fortran_LIBRARY
        NAMES netcdff
        HINTS ${_ncf_lib_hints}
        PATH_SUFFIXES lib lib64
    )

    check_required_args(NetCDF-Fortran
        NAME_MISMATCHED
        REQUIRED_VARS
            NetCDF_Fortran_LIBRARY
            NetCDF_Fortran_INCLUDE_DIR
        FAIL_MESSAGE
            "NetCDF-Fortran not found. Set one of the following:"
            "  - NETCDF_DIR, NETCDF4_DIR, or NETCDF_FORTRAN_ROOT (unified root)"
            "  - NETCDF_INC_DIR + NETCDF_LIB_DIR (split unified, colon-separated paths accepted)"
            "  - NETCDFFORTRAN_INCDIR + NETCDFFORTRAN_LIBDIR (Fortran-specific)"
    )

    if(NOT NetCDF_FOUND)
        return()
    endif()

    add_library(NetCDF::Fortran INTERFACE IMPORTED)
    set_target_properties(NetCDF::Fortran PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${NetCDF_Fortran_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES      "${NetCDF_Fortran_LIBRARY}"
    )
    target_link_libraries(NetCDF::Fortran INTERFACE NetCDF::C)
endif()
