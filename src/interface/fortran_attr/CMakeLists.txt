file(GLOB SRC CONFIGURE_DEPENDS
    "*.f90" "*.F90" "xios_fortran_prefix.hpp")

set_source_files_properties(${SRC} PROPERTIES Fortran_PREPROCESS ON)
target_sources(xios PRIVATE ${SRC})
set_property(GLOBAL APPEND PROPERTY XIOS_INSTALL_SOURCES ${SRC})
target_include_directories(xios PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})