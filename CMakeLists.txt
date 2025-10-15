cmake_minimum_required(VERSION 3.15)
project(ChronoForge2D)

add_executable(ChronoForge2D src/ChronoForge2D.cpp "src/GameObject.cpp" "src/GameObject.hpp")

target_link_libraries(ChronoForge2D 
    opengl32
    gdi32
    user32
)