cmake_minimum_required(VERSION 3.20)
project(Cpp_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cpp_Project main.cpp Maze.cpp Maze.h Game.cpp Game.h Headers.cpp Headers.h Player.cpp Player.h)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Cpp_Project sfml-graphics)