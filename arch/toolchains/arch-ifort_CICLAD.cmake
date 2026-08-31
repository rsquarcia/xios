# ---------------------------------------------------------------------------
# Toolchain for CICLAD – Intel + OpenMPI
# ---------------------------------------------------------------------------

include("${CMAKE_CURRENT_LIST_DIR}/common/intel-openmpi.cmake")

# ---------------------------------------------------------------------------
# Overrides
# ---------------------------------------------------------------------------
set(CMAKE_CXX_COMPILER                              "/usr/lib64/openmpi/1.4.5-ifort/bin/mpicc")
set(CMAKE_Fortran_COMPILER                          "/usr/lib64/openmpi/1.4.5-ifort/bin/mpif90")
