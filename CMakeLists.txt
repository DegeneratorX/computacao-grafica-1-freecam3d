# Versão do CMake
cmake_minimum_required(VERSION 3.22)

# Nome do projeto (pode ser qualquer um)
project(CompGrafica_FreeCam3D)

# (Versão do C++)
set(CMAKE_CXX_STANDARD 17)

# Adiciona o projeto glfw (pasta) no meu projeto. Isso é feito através de uma linkagem com o CMake do glfw.
add_subdirectory(glfw)

# Inclui tudo que estiver dentro da pasta includes
include_directories(includes)

# Procura o OpenGL no SO.
find_package(OpenGL REQUIRED)

# Define os arquivos do projeto para gerar um executável
add_executable(CompGrafica_FreeCam3D src/main.cpp src/glad.c includes/cg1/shader_s.h src/shader_s.cpp)

# Linka as libs ao projeto
target_link_libraries(CompGrafica_FreeCam3D glfw)
target_link_libraries(CompGrafica_FreeCam3D OpenGL::GL)