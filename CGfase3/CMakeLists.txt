cmake_minimum_required(VERSION 3.7)
project(CGfase3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/motor.cpp src/gerador.cpp)
add_executable(CGfase3 ${SOURCE_FILES})