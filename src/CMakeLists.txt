cmake_minimum_required(VERSION 2.8)
set(CMAKE_INSTALL_PREFIX "./")
project(Pigon)

add_library(${PROJECT_NAME} SHARED "pigon.cpp" "matrix.cpp" pigon.rc)

if(WIN32)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "../../build/test/")
else()
    install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION "../../build/test/")
endif()
