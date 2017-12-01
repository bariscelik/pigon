project(PigonProject)
cmake_minimum_required(VERSION 2.8)

include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_DOXYGEN "Build documentation" OFF)
option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (gtest_disable_pthreads on)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(test)
    add_dependencies (pigon_test Pigon)
endif(BUILD_TESTS)

if(BUILD_DOXYGEN)
    add_subdirectory(docs)
endif(BUILD_DOXYGEN)

