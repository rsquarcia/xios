# ---------------------------------------------------------------------------
# Toolchain for Irene-scorep – Intel + OpenMPI
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common/intel-openmpi.cmake")

# ---------------------------------------------------------------------------
# Compiler launcher
# ---------------------------------------------------------------------------
set(CMAKE_CXX_COMPILER_LAUNCHER                     "scorep;--nocompiler;--nomemory;--mpp=mpi;--user")
set(CMAKE_Fortran_COMPILER_LAUNCHER                 "scorep;--nocompiler;--nomemory;--mpp=mpi;--user")

# ---------------------------------------------------------------------------
# Appended flags
# ---------------------------------------------------------------------------
add_flags(CMAKE_CXX_FLAGS                           "-DSCOREP")
add_flags(CMAKE_Fortran_FLAGS_RELEASE               "-g -traceback")

# ---------------------------------------------------------------------------
# Overrides
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS_RELEASE                   "-Ofast -xHost -DBOOST_DISABLE_ASSERTS")
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO            "-g")
set_flags(CMAKE_Fortran_FLAGS                       "-DSCOREP")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO        "-g")
