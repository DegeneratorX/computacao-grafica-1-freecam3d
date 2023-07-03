cmake_minimum_required(VERSION 3.25)
project(CompGrafica_FreeCam3D)

set(CMAKE_CXX_STANDARD 17)

add_executable(CompGrafica_FreeCam3D main.cpp)

add_subdirectory(glfw)
target_link_libraries(CompGrafica_FreeCam3D glfw)

find_package(GLEW REQUIRED)
target_link_libraries(CompGrafica_FreeCam3D GLEW::GLEW)