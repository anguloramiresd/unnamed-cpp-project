cmake_minimum_required(VERSION 3.20)
project(Cpp_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cpp_Project src/main.cpp src/Maze.cpp include/Maze.h src/Game.cpp include/Game.h include/Headers.cpp include/Headers.h src/Player.cpp include/Player.h)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

target_link_libraries(Cpp_Project sfml-graphics)