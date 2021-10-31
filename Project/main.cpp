#include <iostream>
#include "maze.h"

int main() {
    Maze maze(21, 51);
    maze.Generate();
    maze.Print();
    return 0;
}
