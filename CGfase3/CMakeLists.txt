cmake_minimum_required(VERSION 3.7)
project(CGfase3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_1
        tinyxml/tinystr.cpp
        tinyxml/tinystr.h
        tinyxml/tinyxml.cpp
        tinyxml/tinyxml.h
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        src/motor.cpp)

set(SOURCE_FILES_2
        src/gerador.cpp)

add_executable(motor ${SOURCE_FILES_1})
add_executable(gerador ${SOURCE_FILES_2})
add_executable(${PROJECT_NAME} ${SOURCE_FILES_1} ${SOURCE_FILES_2})