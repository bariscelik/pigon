cmake_minimum_required(VERSION 2.8)
set(CMAKE_INSTALL_PREFIX "./")
project(Pigon)

set(PIGON_SOURCE_FILES "pigon.cpp"
                       "matrix.cpp"
                       "matrix.h"
                       "pigon.h"
                       pigon.rc
                       "pigon_global.h")

add_library(${PROJECT_NAME} SHARED ${PIGON_SOURCE_FILES})
