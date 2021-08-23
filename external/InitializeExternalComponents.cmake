find_package(Threads REQUIRED)

if(UNIX)
    find_package(DL REQUIRED)
endif()

include(FetchContent)

# googletest
option(VLD_BUILD_GTEST "Build Gtest for VLD_BUILD_GTEST." ON)
message(STATUS "VLD_BUILD_GTEST:${VLD_BUILD_GTEST}")
if(VLD_BUILD_GTEST)
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.10.0)

    FetchContent_GetProperties(googletest)
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
        include(GoogleTest)
    endif()
endif()

find_package(DbgHelp REQUIRED)