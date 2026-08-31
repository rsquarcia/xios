# FindOASIS.cmake
# Finds the OASIS3-MCT coupling library (psmile.MPI1, scrip, mct, mpeu).
#
# ============================================================
# RESULT VARIABLES
# ============================================================
#
#   OASIS_FOUND          - True if all libraries were found.
#   OASIS_INCLUDE_DIR    - Directory containing mod_prism.mod (psmile.MPI1 build dir).
#   OASIS_PSMILE_LIBRARY - The psmile.MPI1 library.
#   OASIS_SCRIP_LIBRARY  - The SCRIP interpolation library.
#   OASIS_MCT_LIBRARY    - The MCT library.
#   OASIS_MPEU_LIBRARY   - The MPEU utility library.
#
# ============================================================
# IMPORTED TARGETS
# ============================================================
#
#   OASIS::OASIS  — bundles all four OASIS libraries with include dir.
#
# Usage in CMakeLists.txt:
#   find_package(OASIS REQUIRED)
#   target_link_libraries(xios PRIVATE OASIS::OASIS)
#
# ============================================================

include(${CMAKE_CURRENT_LIST_DIR}/helpers.cmake)

if(TARGET OASIS::OASIS)
    return()
endif()

# ---------------------------------------------------------------------------
# Collect path hints from environment variables
# ---------------------------------------------------------------------------

set(_oasis_inc_hints "")
set(_oasis_lib_hints "")

# Root path
foreach(_root_var OASIS_ROOT OASIS_DIR OASIS3_ROOT OASIS3_DIR)
    if(DEFINED ENV{${_root_var}} AND NOT "$ENV{${_root_var}}" STREQUAL "")
        set_if_else(_build BUILD_SHARED_LIBS "build-shared" "build")
        list(APPEND _oasis_inc_hints "$ENV{${_root_var}}/${_build}/lib/psmile.MPI1")
        list(APPEND _oasis_lib_hints "$ENV{${_root_var}}/lib")
    endif()
endforeach()

# Include path
foreach(_inc_var OASIS_INCDIR OASIS_INC_DIR)
    if(DEFINED ENV{${_inc_var}} AND NOT "$ENV{${_inc_var}}" STREQUAL "")
        list(APPEND _oasis_inc_hints "$ENV{${_inc_var}}")
    endif()
endforeach()

# Library path
foreach(_lib_var OASIS_LIBDIR OASIS_LIB_DIR)
    if(DEFINED ENV{${_lib_var}} AND NOT "$ENV{${_lib_var}}" STREQUAL "")
        list(APPEND _oasis_lib_hints "$ENV{${_lib_var}}")
    endif()
endforeach()

# Standard MODIPSL build location.
set(_oasis_root "${CMAKE_SOURCE_DIR}/../../oasis3-mct/BLD")
set_if_else(_build BUILD_SHARED_LIBS "build-shared" "build")

list(APPEND _oasis_inc_hints "${_oasis_root}/${_build}/lib/psmile.MPI1")
list(APPEND _oasis_lib_hints "${_oasis_root}/lib")

# ---------------------------------------------------------------------------
# Locate Fortran module directory and libraries
# ---------------------------------------------------------------------------

find_path(OASIS_INCLUDE_DIR
    NAMES mod_prism.mod
    HINTS ${_oasis_inc_hints}
)

find_lib_suffixed(OASIS_PSMILE_LIBRARY
    NAMES psmile.MPI1
    HINTS ${_oasis_lib_hints}
)

find_lib_suffixed(OASIS_SCRIP_LIBRARY
    NAMES scrip
    HINTS ${_oasis_lib_hints}
)

find_lib_suffixed(OASIS_MCT_LIBRARY
    NAMES mct
    HINTS ${_oasis_lib_hints}
)

find_lib_suffixed(OASIS_MPEU_LIBRARY
    NAMES mpeu
    HINTS ${_oasis_lib_hints}
)

# ---------------------------------------------------------------------------
# Check that all components were found
# ---------------------------------------------------------------------------

check_required_args(OASIS
    REQUIRED_VARS
        OASIS_PSMILE_LIBRARY
        OASIS_SCRIP_LIBRARY
        OASIS_MCT_LIBRARY
        OASIS_MPEU_LIBRARY
        OASIS_INCLUDE_DIR
    FAIL_MESSAGE
        "OASIS3-MCT not found. Set one of the following:"
        "  - OASIS_INCDIR + OASIS_LIBDIR (separate include/lib paths)"
        "  - OASIS_ROOT (root of OASIS3-MCT build tree, e.g. /path/to/oasis3-mct/BLD)"
)

if(NOT OASIS_FOUND)
    return()
endif()

# OASIS depends on NetCDF-Fortran internally (libpsmile calls nf90_* routines)
find_package(NetCDF REQUIRED COMPONENTS Fortran)

# ---------------------------------------------------------------------------
# Create the IMPORTED target
# ---------------------------------------------------------------------------

if(NOT TARGET OASIS::OASIS)
    add_library(OASIS::OASIS INTERFACE IMPORTED)
    set_target_properties(OASIS::OASIS PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${OASIS_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES      "${OASIS_PSMILE_LIBRARY};${OASIS_SCRIP_LIBRARY};${OASIS_MCT_LIBRARY};${OASIS_MPEU_LIBRARY}"
    )
    target_link_libraries(OASIS::OASIS INTERFACE NetCDF::Fortran)
endif()
