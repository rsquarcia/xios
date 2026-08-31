file(GLOB SRC CONFIGURE_DEPENDS "src/*.cpp")

add_library(cpptrace OBJECT ${SRC})

target_include_directories(cpptrace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(cpptrace PROPERTIES POSITION_INDEPENDENT_CODE ON)