# ---------------------------------------------------------------------------
# Cray – MPICH (CC / ftn)
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common.cmake")

# ---------------------------------------------------------------------------
# Compilers
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_COMPILER                     CC)
set_flags(CMAKE_Fortran_COMPILER                 ftn)

# ---------------------------------------------------------------------------
# Compiler flags
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS                        "-D__XIOS_EXCEPTION")
set_flags(CMAKE_CXX_FLAGS_RELEASE                "-O3 -DBOOST_DISABLE_ASSERTS")
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO         "-g -O2")
set_flags(CMAKE_CXX_FLAGS_DEBUG                  "-g")

set_flags(CMAKE_Fortran_FLAGS                    "-M 878")
set_flags(CMAKE_Fortran_FLAGS_RELEASE            "-O3")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO     "-g -O2")
set_flags(CMAKE_Fortran_FLAGS_DEBUG              "-g")
