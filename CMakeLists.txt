cmake_minimum_required(VERSION 3.2)

project(fourier)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTION "-Wall; -Wpedantic;-Wextra"
)
include_directories( ${OPENGL_INCLUDE_DIRS}, ${GLUT_INCLUDE_DIRS})

target_link_libraries(fourier ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
