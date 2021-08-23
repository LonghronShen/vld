cmake_minimum_required(VERSION 3.16)

project(vld-lib C CXX)

file(
  GLOB_RECURSE
  src
  ${CMAKE_CURRENT_LIST_DIR}/*.h
  ${CMAKE_CURRENT_LIST_DIR}/*.hpp
  ${CMAKE_CURRENT_LIST_DIR}/*.c
  ${CMAKE_CURRENT_LIST_DIR}/*.cc
  ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

file(GLOB_RECURSE natvis_src ${CMAKE_CURRENT_LIST_DIR}/*.natvis)

set(public_headers ${CMAKE_CURRENT_LIST_DIR}/vld.h
                   ${CMAKE_CURRENT_LIST_DIR}/vld_def.h)

foreach(res IN ITEMS ${public_headers})
  get_filename_component(res_file_name ${res} NAME)
  message(STATUS "Generating public headers: ${res_file_name} ...")
  configure_file(
    ${res} ${CMAKE_CURRENT_BINARY_DIR}/include/vld/${res_file_name} COPYONLY)
endforeach()

add_library(vld SHARED ${src} ${natvis_src})
add_library(vld::vld ALIAS vld-lib)

target_link_libraries(vld PUBLIC DbgHelp::DbgHelp)

target_include_directories(vld PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include/")
