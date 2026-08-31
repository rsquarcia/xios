add_subdirectory(c)
add_subdirectory(c_attr)
add_subdirectory(fortran)
add_subdirectory(fortran_attr)

file(GLOB PYTHON_SRC CONFIGURE_DEPENDS "python/xios/*.py")
set_property(GLOBAL APPEND PROPERTY XIOS_INSTALL_PYTHON ${PYTHON_SRC})