#include <iostream>
#include <vector>

#define Wall '#'
const size_t kWidth = 301;
const size_t kHeight = 51;

typedef std::vector<std::vector<char>> Grid;

void PrintGrid(const Grid &maze) {
    for (size_t i = 0; i < kHeight; ++i) {
        for (size_t j = 0; j < kWidth; ++j)
            std::cout << maze[i][j];
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool Valid(size_t x, size_t y, const Grid &maze) {
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    int new_x, new_y, c = 0;

    for (size_t i = 0; i < 4; ++i) {
        new_x = x + dx[i];
        new_y = y + dy[i];
        if (new_x >= 1 && new_x < kHeight - 1 && new_y >= 1 && new_y < kWidth - 1)
            if (maze[new_x][new_y] == ' ')
                c++;
    }
    return (x >= 1 && x < kHeight - 1 && y >= 1 && y < kWidth - 1 && maze[x][y] == Wall && c == 1);
}

void CreateLabyrinth(size_t x, size_t y, Grid &maze) {
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    size_t order[] = {0, 1, 2, 3};
    size_t new_x, new_y;
    maze[x][y] = ' ';

    for (size_t i = 0; i < 10; ++i)
        std::swap(order[rand() % 4], order[rand() % 4]);

    for (size_t i = 0; i < 4; ++i) {
        new_x = x + dx[order[i]];
        new_y = y + dy[order[i]];
        if (Valid(new_x, new_y, maze))
            CreateLabyrinth(new_x, new_y, maze);
    }
}

int main() {
    Grid maze(kHeight, std::vector<char>(kWidth, Wall));
    srand(time(NULL));
    CreateLabyrinth(1, 1, maze);
    PrintGrid(maze);
    return 0;
}
