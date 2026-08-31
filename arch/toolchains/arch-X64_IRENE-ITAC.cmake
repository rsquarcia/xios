# ---------------------------------------------------------------------------
# Toolchain for Irene-itac – Intel + OpenMPI
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common/intel-openmpi.cmake")

# ---------------------------------------------------------------------------
# Appended flags
# ---------------------------------------------------------------------------
add_flags(CMAKE_CXX_FLAGS                           "-trace -DITAC -I$ENV{ITAC_INCDIR}")
add_flags(CMAKE_Fortran_FLAGS_RELEASE               "-g -traceback")

# ---------------------------------------------------------------------------
# Overrides
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS_RELEASE                   "-g -Ofast -xHost -DBOOST_DISABLE_ASSERTS")
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO            "-g")
set_flags(CMAKE_Fortran_FLAGS                       "-trace")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO        "-g")
set_flags(CMAKE_EXE_LINKER_FLAGS                    "-trace -L$ENV{ITAC_LIBDIR}")
