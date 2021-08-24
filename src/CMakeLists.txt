cmake_minimum_required(VERSION 3.16)

project(vld-lib C CXX)

file(
  GLOB
  src
  ${CMAKE_CURRENT_LIST_DIR}/*.h
  ${CMAKE_CURRENT_LIST_DIR}/*.hpp
  ${CMAKE_CURRENT_LIST_DIR}/*.c
  ${CMAKE_CURRENT_LIST_DIR}/*.cc
  ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

file(GLOB natvis_src ${CMAKE_CURRENT_LIST_DIR}/*.natvis)

file(GLOB rc_src ${CMAKE_CURRENT_LIST_DIR}/*.rc)

if(IsX64)
  set(VLD_MANIFEST ${CMAKE_CURRENT_LIST_DIR}/vld.dll.dependency.x64.manifest)
else()
  set(VLD_MANIFEST ${CMAKE_CURRENT_LIST_DIR}/vld.dll.dependency.x86.manifest)
endif()

set(public_headers ${CMAKE_CURRENT_LIST_DIR}/vld.h
                   ${CMAKE_CURRENT_LIST_DIR}/vld_def.h)

foreach(res IN ITEMS ${public_headers})
  get_filename_component(res_file_name ${res} NAME)
  message(STATUS "Generating public headers: ${res_file_name} ...")
  configure_file(${res} ${CMAKE_CURRENT_BINARY_DIR}/include/${res_file_name}
                 COPYONLY)
endforeach()

add_library(vld SHARED ${src} ${natvis_src} ${VLD_MANIFEST})
add_library(vld::vld ALIAS vld)

target_compile_definitions(
  vld
  PRIVATE "_WIN32_WINNT=0x0501"
  PRIVATE "_USRDLL"
  PRIVATE "_UNICODE"
  PRIVATE "UNICODE"
  PRIVATE "VLDBUILD"
  PRIVATE "USE_CMAKE_DBGHELP"
  PRIVATE "USE_FMT")

target_link_libraries(
  vld
  PUBLIC DbgHelp::DbgHelp
  PRIVATE fmt::fmt)

target_include_directories(
  vld
  PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../setup/"
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include/")
