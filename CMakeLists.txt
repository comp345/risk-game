cmake_minimum_required(VERSION 3.0.0)
project(HelloWorld VERSION 0.1.0)

include(CTest)
enable_testing()

# add_executable(HelloWorld main.cpp)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(HelloWorld ${SRC_FILES} src/Player.cpp src/Player.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
