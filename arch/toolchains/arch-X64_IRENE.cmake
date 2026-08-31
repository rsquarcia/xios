# ---------------------------------------------------------------------------
# Toolchain for Irene – Intel + OpenMPI
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common/intel-openmpi.cmake")

# ---------------------------------------------------------------------------
# Overrides
# ---------------------------------------------------------------------------
set_flags(CMAKE_CXX_FLAGS_RELWITHDEBINFO            "-g")
set_flags(CMAKE_Fortran_FLAGS_RELWITHDEBINFO        "-g")
