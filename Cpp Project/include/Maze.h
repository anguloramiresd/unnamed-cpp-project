//
// Created by dieguin on 12/12/21.
//

#ifndef CPP_PROJECT_MAZE_H
#define CPP_PROJECT_MAZE_H

#include <vector>
#include <random>

const int kDx[] = {1, -1, 0, 0};
const int kDy[] = {0, 0, -1, 1};

class Maze {
public:
    constexpr static const char kEmpty = ' ';
    constexpr static const char kWall = '#';
    constexpr static const char kApple = '-';
    uint16_t apples_;

private:
    std::vector<std::vector<char>> grid_;
    size_t height_, width_;
    std::random_device seed_;
    std::mt19937 engine_;
    std::uniform_int_distribution<> randomizer_;
    std::uniform_int_distribution<> random_width_;
    std::uniform_int_distribution<> random_height_;

public:
    Maze(size_t height, size_t width, uint16_t apples);

    void Print() const;

    void Generate();

    char GetCell(size_t pos_x, size_t pos_y);

    void EatApple(size_t pos_x, size_t pos_y);

private:
    bool Valid(int x, int y) const;

    void CreateLabyrinth(int x, int y);

    void AddApples();
};

#endif //CPP_PROJECT_MAZE_H
