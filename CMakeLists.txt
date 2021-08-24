cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(vld-proj C CXX)

message(STATUS "Operation system is ${CMAKE_SYSTEM}")

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
  message(STATUS "Target is 64 bits")
  set(IsX64 true)
else()
  message(STATUS "Target is 32 bits")
  set(IsX64 false)
endif()

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  message(STATUS "Has a parent scope.")
else()
  message(STATUS "Doesn't have a parent scope.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      ${CMAKE_BINARY_DIR}/bin
      CACHE STRING "CMAKE_LIBRARY_OUTPUT_DIRECTORY" FORCE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      ${CMAKE_BINARY_DIR}/bin
      CACHE STRING "CMAKE_RUNTIME_OUTPUT_DIRECTORY" FORCE)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      ${CMAKE_BINARY_DIR}/bin
      CACHE STRING "CMAKE_ARCHIVE_OUTPUT_DIRECTORY" FORCE)

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_BINARY_DIR}/bin
      CACHE STRING "CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG" FORCE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
      ${CMAKE_BINARY_DIR}/bin
      CACHE STRING "CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG" FORCE)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(BuildForWinXP)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_STANDARD
    17
    CACHE STRING
          "Set to 11 or 14 to enable C++11 or C++17 builds, respectively."
          FORCE)
set(CMAKE_C_STANDARD
    17
    CACHE STRING "Set to 99 or 11 to enable C99 or C11 builds, respectively."
          FORCE)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY C_STANDARD_REQUIRED ON)

add_compile_definitions("__STDC_WANT_LIB_EXT1__=1")

if(WIN32)
  add_compile_definitions("WIN32_LEAN_AND_MEAN" "_CRT_SECURE_NO_WARNINGS"
                          "NOMINMAX")
  if(MSVC)
    add_compile_definitions("__extension__")
    add_compile_options("/source-charset:utf-8")

    if((NOT CMAKE_BUILD_TYPE) OR (NOT CMAKE_BUILD_TYPE STREQUAL "Debug"))
      add_compile_options("/MT")
    else()
      add_compile_options("/MTd")
    endif()

    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELWITHDEBINFO)
    foreach(CompilerFlag ${CompilerFlags})
      string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
      set(${CompilerFlag}
          "${${CompilerFlag}}"
          CACHE STRING "msvc compiler flags" FORCE)
      message("MSVC flags: ${CompilerFlag}:${${CompilerFlag}}")
    endforeach()
  endif()
else()
  message(FATAL_ERROR "Unix-like OS is not supported.")
endif()

include(external/InitializeExternalComponents.cmake)

add_subdirectory(src)

configure_file("${CMAKE_CURRENT_LIST_DIR}/vld.ini"
               "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vld.ini" COPYONLY)
