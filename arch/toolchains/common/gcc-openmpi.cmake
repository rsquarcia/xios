# ---------------------------------------------------------------------------
# GCC – OpenMPI wrappers (mpic++ / mpif90)
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common.cmake")

# ---------------------------------------------------------------------------
# Compilers
# ---------------------------------------------------------------------------
set(CMAKE_CXX_COMPILER                           mpic++)
set(CMAKE_Fortran_COMPILER                       mpif90)

# ---------------------------------------------------------------------------
# C++ flags
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS                        "-w -D__XIOS_EXCEPTION")
set_flags(CMAKE_CXX_FLAGS_RELEASE                "-O3 -DBOOST_DISABLE_ASSERTS")
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO         "-g -O2")
set_flags(CMAKE_CXX_FLAGS_DEBUG                  "-g")

# ---------------------------------------------------------------------------
# Fortran flags
# ---------------------------------------------------------------------------
set_flags(CMAKE_Fortran_FLAGS                    "-ffree-line-length-none")
set_flags(CMAKE_Fortran_FLAGS_RELEASE            "-O3")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO     "-g -O2")
set_flags(CMAKE_Fortran_FLAGS_DEBUG              "-g")

# ---------------------------------------------------------------------------
# Linker flags
# ---------------------------------------------------------------------------
set_flags(CMAKE_EXE_LINKER_FLAGS                 "-pthread")
set_flags(CMAKE_Fortran_STANDARD_LIBRARIES       "-lstdc++")
