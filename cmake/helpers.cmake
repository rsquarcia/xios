# helpers.cmake - CMake helper functions for XIOS

# Check required arguments for a package and report a custom failure message if
# any are missing.
macro(check_required_args PACKAGE_NAME)
    cmake_parse_arguments(
        _CRA
        "NAME_MISMATCHED"
        ""
        "REQUIRED_VARS;FAIL_MESSAGE"
    ${ARGN})

    string(JOIN "\n" _cra_fail_msg ${_CRA_FAIL_MESSAGE})

    include(FindPackageHandleStandardArgs)
    if(_CRA_NAME_MISMATCHED)
        find_package_handle_standard_args(${PACKAGE_NAME}
            REQUIRED_VARS ${_CRA_REQUIRED_VARS}
            FAIL_MESSAGE  "${_cra_fail_msg}"
            NAME_MISMATCHED
        )
        # Propagate result to the calling find module's _FOUND variable
        set(_cra_found_var "${PACKAGE_NAME}_FOUND")
        set(${CMAKE_FIND_PACKAGE_NAME}_FOUND "${${_cra_found_var}}")
        unset(_cra_found_var)
    else()
        find_package_handle_standard_args(${PACKAGE_NAME}
            REQUIRED_VARS ${_CRA_REQUIRED_VARS}
            FAIL_MESSAGE  "${_cra_fail_msg}"
        )
    endif()
endmacro()

# Split a colon-separated environment variable into a CMake list.
macro(_split_colon _envvar _out_list)
    set(${_out_list} "")
    if(DEFINED ENV{${_envvar}} AND NOT "$ENV{${_envvar}}" STREQUAL "")
        string(REPLACE ":" ";" ${_out_list} "$ENV{${_envvar}}")
    endif()
endmacro()

# Add XIOS executable with Fortran or C++ linker language.
macro(add_xios_executable name src linker_lang)
    add_executable(${name} ${src})
    set_property(TARGET ${name} PROPERTY LINKER_LANGUAGE ${linker_lang})
    target_link_libraries(${name} PRIVATE xios)
    list(APPEND XIOS_EXECUTABLES ${name})
    install(PROGRAMS $<TARGET_FILE:${name}> DESTINATION bin RENAME ${name}.exe)
endmacro()

# Find a library with the appropriate suffix for the current build type.
function(find_lib_suffixed VAR)
    cmake_parse_arguments(PARSE_ARGV 1 ARG "" "" "NAMES;HINTS")

    if(BUILD_SHARED_LIBS)
        set(_suffix ".so")
    else()
        set(_suffix ".a")
    endif()

    set(_names)
    foreach(_name ${ARG_NAMES})
        list(APPEND _names "lib${_name}${_suffix}")
    endforeach()

    find_library(${VAR}
        NAMES ${_names}
        HINTS ${ARG_HINTS}
        PATH_SUFFIXES lib lib64
    )
endfunction()

# Install the files accumulated in a global property, named by FILES.
# Subdirectories append whole glob results, so the compiled sources they
# contain are dropped here and only the shippable files are installed.
function(install_sources)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "" "FILES;DESTINATION" "")

    get_property(_files GLOBAL PROPERTY ${ARG_FILES})
    list(FILTER _files EXCLUDE REGEX "\\.(cpp|cxx|cc|c|f|F|f90|F90)$")

    if(NOT _files)
        return()
    endif()

    install(FILES ${_files} DESTINATION ${ARG_DESTINATION})
endfunction()

# Set VAR to TRUE_VAL if COND is true, else FALSE_VAL.
macro(set_if_else VAR COND TRUE_VAL FALSE_VAL)
    if(${COND})
        set(${VAR} ${TRUE_VAL})
    else()
        set(${VAR} ${FALSE_VAL})
    endif()
endmacro()