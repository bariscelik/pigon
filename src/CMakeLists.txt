cmake_minimum_required(VERSION 2.8)
set(CMAKE_INSTALL_PREFIX "./")
project(Pigon)

include_directories("../include")

file(GLOB_RECURSE PIGON_SOURCE_FILES "pigon.rc"
                             "*.cpp"
                             "../include/*.h")


add_library(${PROJECT_NAME} SHARED ${PIGON_SOURCE_FILES})
