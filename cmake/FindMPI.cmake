# FindMPI.cmake
# Wraps CMake's own FindMPI module, adding a Cray MPICH fix-up.
#
# ============================================================
# IMPORTED TARGETS
# ============================================================
#
#   MPI::MPI_CXX     — from CMake's FindMPI module.
#   MPI::MPI_Fortran — from CMake's FindMPI module; on Cray MPICH, augmented
#                      with the real Fortran binding library (see below).
#
# ============================================================

include("${CMAKE_ROOT}/Modules/FindMPI.cmake")

# Add MPI Fortran lib for Cray compiler (CC driver only handles C++ bindings)
if(TARGET MPI::MPI_Fortran AND DEFINED ENV{CRAY_MPICH_DIR})
    find_library(_mpi_cray_fortran_lib
        NAMES mpifort_cray
        HINTS "$ENV{CRAY_MPICH_DIR}/lib"
    )

    if(_mpi_cray_fortran_lib)
        set_property(TARGET MPI::MPI_Fortran APPEND
                     PROPERTY INTERFACE_LINK_LIBRARIES "${_mpi_cray_fortran_lib}")
        message(STATUS "XIOS: augmented MPI::MPI_Fortran with ${_mpi_cray_fortran_lib}")
    endif()
endif()
