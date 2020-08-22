cmake_minimum_required(VERSION 2.6.0)
project(myGL)
set(CMAKE_CXX_STANDARD 14)

add_executable(myGL src/main.cpp)
include_directories(myGL include/ src/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/dep/GLFW)
target_link_libraries(myGL glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(myGL OpenGL::GL)

