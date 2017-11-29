cmake_minimum_required(VERSION 2.8)
project(pigon_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (gtest_disable_pthreads on)

# GOOGLETEST
add_subdirectory(googletest-release-1.8.0)
config_compiler_and_linker()

# PIGON
set(PIGON_INCLUDE_DIR "../src/")
find_library(PIGON_LIBRARY Pigon "../build/pigon/")
include_directories(${PIGON_INCLUDE_DIR})

add_executable(${PROJECT_NAME} "main.cpp")
add_test(${PROJECT_NAME} COMMAND ${PROJECT_NAME})

FILE(GLOB_RECURSE LibFiles "*.h")
add_custom_target(headers SOURCES ${LibFiles})

target_link_libraries(${PROJECT_NAME} ${PIGON_LIBRARY} gtest gmock)
