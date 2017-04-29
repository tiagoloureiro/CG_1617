cmake_minimum_required(VERSION 3.6)
project(CGfase2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        gerador/main.cpp
        motor/tinyxml/tinystr.cpp
        motor/tinyxml/tinystr.h
        motor/tinyxml/tinyxml.cpp
        motor/tinyxml/tinyxml.h
        motor/tinyxml/tinyxmlerror.cpp
        motor/tinyxml/tinyxmlparser.cpp
        motor/main.cpp)

add_executable(CGfase2 ${SOURCE_FILES})