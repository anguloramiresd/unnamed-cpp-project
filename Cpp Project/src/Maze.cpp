//
// Created by dieguin on 12/12/21.
//

#include "../include/Headers.h"
#include "Maze.h"

Maze::Maze(const size_t height, const size_t width, uint16_t apples) : height_(height), width_(width), apples_(apples) {
    grid_.assign(height, std::vector<char>(width, '#'));
    engine_ = std::mt19937(seed_());
    randomizer_ = std::uniform_int_distribution<>(0, 3);
    random_height_ = std::uniform_int_distribution<>(0, int(height_));
    random_width_ = std::uniform_int_distribution<>(0, int(width_));
}

void Maze::Print() const {
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            std::cout << grid_[i][j];
}
        std::cout << '\n';
    }
}

void Maze::Generate() {
    CreateLabyrinth(1, 1);
    AddApples();
}

char Maze::GetCell(const size_t pos_x, const size_t pos_y){
    return grid_[pos_x][pos_y];
}

bool Maze::Valid(const int x, const int y) const {
    int new_x;
    int new_y;
    int c = 0;

    for (size_t i = 0; i < 4; ++i) {
        new_x = x + kDx[i];
        new_y = y + kDy[i];
        if (new_x >= 1 && new_x < height_ - 1 && new_y >= 1 && new_y < width_ - 1) {
            if (grid_[new_x][new_y] == ' ') {
                c++;
}
}
    }
    return (x >= 1 && x < height_ - 1 && y >= 1 && y < width_ - 1 && grid_[x][y] == kWall && c == 1);
}

void Maze::CreateLabyrinth(const int x, const int y) {
    int order[] = {0, 1, 2, 3};
    int new_x;
    int new_y;
    grid_[x][y] = kEmpty;

    for (size_t i = 0; i < 10; ++i) {
        std::swap(order[randomizer_(engine_)], order[randomizer_(engine_)]);
}

    for (size_t i: order) {
        new_x = x + kDx[i];
        new_y = y + kDy[i];
        if (Valid(new_x, new_y)) {
            CreateLabyrinth(new_x, new_y);
}
    }
}

void Maze::AddApples() {
    int x;
    int y;
    int c = 0;
    while(c < apples_){
        x = random_height_(engine_);
        y = random_width_(engine_);
        if(grid_[x][y] != kWall && grid_[x][y] != kApple) {
            grid_[x][y] = kApple;
            c++;
        }
    }
}

void Maze::EatApple(size_t pos_x, size_t pos_y) {
    grid_[pos_x][pos_y] = kEmpty;
}
