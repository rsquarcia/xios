# ---------------------------------------------------------------------------
# Toolchain for Irene (GNU) – GCC + OpenMPI
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common/gcc-openmpi.cmake")

# ---------------------------------------------------------------------------
# Appended flags
# ---------------------------------------------------------------------------
add_flags(CMAKE_CXX_FLAGS                           "-fpermissive")
add_flags(CMAKE_CXX_FLAGS_DEBUG                     "-DBZ_DEBUG -fbacktrace -fno-inline")
add_flags(CMAKE_Fortran_FLAGS_DEBUG                 "-fbacktrace")

# ---------------------------------------------------------------------------
# Overrides
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO            "-g")
set_flags(CMAKE_Fortran_FLAGS                       "--free-form -ffree-line-length-0")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO        "-g")
