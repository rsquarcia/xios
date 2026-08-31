# config-init.cmake - CMake configure setup script

# ---------------------------------------------------------------------------
# Toolchain setup
# ---------------------------------------------------------------------------

# Cache XIOS_ENV_ARCH so it survives a rebuild
if (DEFINED ENV{XIOS_ENV_ARCH})
    set(XIOS_ENV_ARCH "$ENV{XIOS_ENV_ARCH}" CACHE INTERNAL "Architecture XIOS was configured for")
elseif (NOT XIOS_ENV_ARCH)
    message(FATAL_ERROR "XIOS_ENV_ARCH variable is not set. Please set it or run the make_xios script to set up the build environment.")
endif()

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/arch/arch-${XIOS_ENV_ARCH}.fcm")

execute_process(
    COMMAND python3 "${CMAKE_SOURCE_DIR}/arch/gen_toolchain.py" "${XIOS_ENV_ARCH}"
    RESULT_VARIABLE _gen_toolchain_result
)

if(NOT _gen_toolchain_result EQUAL 0)
    message(FATAL_ERROR "Failed to generate toolchain file for architecture ${XIOS_ENV_ARCH}.")
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/arch/toolchains/arch-${XIOS_ENV_ARCH}.cmake" CACHE STRING "" FORCE)

# ---------------------------------------------------------------------------
# Architecture environment file
# ---------------------------------------------------------------------------

# Mirror arch/arch-<ARCH>.env into the build tree, so that tooling needing this
# build's runtime environment (run_tests, perf/bench.py) has one stable path to
# source.
set(_xios_arch_env "${CMAKE_SOURCE_DIR}/arch/arch-${XIOS_ENV_ARCH}.env")
if(EXISTS "${_xios_arch_env}")
    configure_file("${_xios_arch_env}" "${CMAKE_BINARY_DIR}/arch.env" COPYONLY)
else()
    message(STATUS "No arch-${XIOS_ENV_ARCH}.env in arch/ -- ${CMAKE_BINARY_DIR}/arch.env not written")
endif()
unset(_xios_arch_env)

# ---------------------------------------------------------------------------
# Modules, commands
# ---------------------------------------------------------------------------

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}" CACHE STRING "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

# ---------------------------------------------------------------------------
# Output directories
# ---------------------------------------------------------------------------

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") # static libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") # shared libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # executables