cmake_minimum_required(VERSION 2.8)
project(pigon_test)

set (gtest_disable_pthreads on)

# GOOGLETEST
add_subdirectory(googletest-release-1.8.0)
config_compiler_and_linker()

# PIGON
include_directories("../src/")

add_executable(${PROJECT_NAME} "main.cpp" "matrix_test.h")

target_link_libraries(${PROJECT_NAME} Pigon gtest gmock)
