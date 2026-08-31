# ---------------------------------------------------------------------------
# Toolchain for XC30_Cray – Cray + MPICH
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common/cray-mpich.cmake")

# ---------------------------------------------------------------------------
# Appended flags
# ---------------------------------------------------------------------------
add_flags(CMAKE_CXX_FLAGS                           "-hstd=c++11 -DMPICH_SKIP_MPICXX -h msglevel_4 -h zero -h gnu")

# ---------------------------------------------------------------------------
# Overrides
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS_RELEASE                   "-O1 -DBOOST_DISABLE_ASSERTS")
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO            "-O2")
set_flags(CMAKE_Fortran_FLAGS                       "-em -m 4 -e0 -eZ")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO        "-G2")
