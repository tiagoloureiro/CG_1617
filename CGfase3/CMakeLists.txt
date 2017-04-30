cmake_minimum_required(VERSION 3.7)
project(CGfase3)

set(CMAKE_CXX_STANDARD 11)

if (NOT APPLE)
    if (WIN32)
        set(GLEW_ROOT_FOLDER "" CACHE PATH "Path to GLEW folder")
        include_directories(${GLEW_ROOT_FOLDER})
        link_directories(${GLEW_ROOT_FOLDER})
    else(WIN32)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif(WIN32)
endif(NOT APPLE)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

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

if (WIN32)
    target_link_libraries(motor ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glew32)
else(WIN32)
    target_link_libraries(motor ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif (WIN32)