find_package(Threads REQUIRED)

if(UNIX)
  find_package(DL REQUIRED)
endif()

include(FetchContent)

# googletest
option(VLD_BUILD_GTEST "Build Gtest for VLD_BUILD_GTEST." ON)
message(STATUS "VLD_BUILD_GTEST:${VLD_BUILD_GTEST}")
if(VLD_BUILD_GTEST)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.10.0)

  FetchContent_GetProperties(googletest)
  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR}
                     EXCLUDE_FROM_ALL)
    include(GoogleTest)
  endif()
endif()

# fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG ef7369ce900346f403472231b60662936b24e731)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

find_package(DbgHelp REQUIRED)
