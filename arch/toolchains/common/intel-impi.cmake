# ---------------------------------------------------------------------------
# Intel compilers – IntelMPI wrappers (mpiicpc / mpiifort)
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common.cmake")

# ---------------------------------------------------------------------------
# Compilers
# ---------------------------------------------------------------------------
set(CMAKE_CXX_COMPILER                          mpiicpc)
set(CMAKE_Fortran_COMPILER                      mpiifort)

# ---------------------------------------------------------------------------
# C++ flags
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS                       "-diag-disable 1125 -diag-disable 279 -D__XIOS_EXCEPTION")
set_flags(CMAKE_CXX_FLAGS_RELEASE               "-O3 -DBOOST_DISABLE_ASSERTS")
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO        "-g -O2 -traceback")
set_flags(CMAKE_CXX_FLAGS_DEBUG                 "-DBZ_DEBUG -g -traceback -fno-inline")

# ---------------------------------------------------------------------------
# Fortran flags
# ---------------------------------------------------------------------------
set_flags(CMAKE_Fortran_FLAGS_RELEASE           "-O3")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO    "-g -O2 -traceback")
set_flags(CMAKE_Fortran_FLAGS_DEBUG             "-g -traceback")