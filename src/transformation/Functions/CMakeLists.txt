file(GLOB SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

target_sources(xios PRIVATE ${SRC})
set_property(GLOBAL APPEND PROPERTY XIOS_INSTALL_SOURCES ${SRC})
target_include_directories(xios PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})