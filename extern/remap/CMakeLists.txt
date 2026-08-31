file(GLOB SRC CONFIGURE_DEPENDS "src/*.cpp")

# remap depends on some XIOS source files, so to avoid circular linking
# difficulties we just add it to the main XIOS library sources.
target_sources(xios PRIVATE ${SRC})
target_include_directories(xios PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)