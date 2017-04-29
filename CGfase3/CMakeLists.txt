cmake_minimum_required(VERSION 3.7)
project(CGfase3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_1
        lib/tinyxml/tinystr.cpp
        lib/tinyxml/tinystr.h
        lib/tinyxml/tinyxml.cpp
        lib/tinyxml/tinyxml.h
        lib/tinyxml/tinyxmlerror.cpp
        lib/tinyxml/tinyxmlparser.cpp
        src/motor.cpp)

set(SOURCE_FILES_2
        src/gerador.cpp)

add_executable(motor ${SOURCE_FILES_1})
add_executable(gerador ${SOURCE_FILES_2})
add_executable(${PROJECT_NAME} ${SOURCE_FILES_1} ${SOURCE_FILES_2})