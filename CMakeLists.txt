cmake_minimum_required(VERSION 3.10.0)
project(TETRIS VERSION 0.1.0)

find_package(OpenGL REQUIRED)

add_executable(TETRIS 
                src/main.cpp
                src/glad.c
                src/Shader.hpp
                src/Shader.cpp
                #src/stb_image.h
                src/stb_image_implementation.cpp
)

target_link_libraries(TETRIS 
                                glfw
                                OpenGL::GL
)