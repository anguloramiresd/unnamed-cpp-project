#ifndef PROJECT_MAZE_H
#define PROJECT_MAZE_H

#endif //PROJECT_MAZE_H

#include <vector>
#include <random>

#define Wall '#'

class Maze {
private:
    std::vector<std::vector<char>> grid_;
    size_t height_, width_;
    std::random_device seed_;
    std::mt19937 engine_;
    std::uniform_int_distribution<> randomizer_;
    constexpr static const int dx[] = {1, -1, 0, 0};
    constexpr static const int dy[] = {0, 0, -1, 1};

public:
    Maze(const size_t height, const size_t width) : height_(height), width_(width) {
        grid_.assign(height, std::vector<char>(width, Wall));
        engine_ = std::mt19937(seed_());
        randomizer_ = std::uniform_int_distribution<>(0, 3);
    }

    void Print() {
        for (size_t i = 0; i < height_; ++i) {
            for (size_t j = 0; j < width_; ++j)
                std::cout << grid_[i][j];
            std::cout << '\n';
        }
    }

    void Generate() {
        CreateLabyrinth(1, 1);
    }

private:
    [[nodiscard]] bool Valid(const int x, const int y) const {
        int new_x, new_y, c = 0;

        for (size_t i = 0; i < 4; ++i) {
            new_x = x + dx[i];
            new_y = y + dy[i];
            if (new_x >= 1 && new_x < height_ - 1 && new_y >= 1 && new_y < width_ - 1)
                if (grid_[new_x][new_y] == ' ')
                    c++;
        }
        return (x >= 1 && x < height_ - 1 && y >= 1 && y < width_ - 1 && grid_[x][y] == Wall && c == 1);
    }

    void CreateLabyrinth(const int x, const int y) {
        int order[] = {0, 1, 2, 3};
        int new_x, new_y;
        grid_[x][y] = ' ';

        for (size_t i = 0; i < 10; ++i)
            std::swap(order[randomizer_(engine_)], order[randomizer_(engine_)]);

        for (size_t i: order) {
            new_x = x + dx[i];
            new_y = y + dy[i];
            if (Valid(new_x, new_y))
                CreateLabyrinth(new_x, new_y);
        }
    }
};