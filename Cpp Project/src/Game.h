//
// Created by dieguin on 12/12/21.
//

#ifndef CPP_PROJECT_GAME_H
#define CPP_PROJECT_GAME_H

#include "../include/Headers.h"
#include "Maze.h"
#include "Player.h"

class Game {
private:
    uint16_t height_;
    uint16_t width_;
    Maze *labyrinth_;
    sf::RenderWindow *window_;
    sf::Clock clock_;
    sf::Texture cobble_;
    sf::Texture dirt_;
    sf::Texture animal_;
    sf::Texture fruit_;
    sf::Sprite wall_;
    sf::Sprite road_;
    sf::Sprite sheep_;
    sf::Sprite apple_;
    sf::Event event_{};
    Player *player_;

public:
    Game(size_t height, size_t width);
    ~Game();
    void Play();
private:
    void Update();
    void Render();
    void DrawLabyrinth();
    void DrawPlayer();
    void CaptureKey();
    void WasThatAnApple();
};

#endif //CPP_PROJECT_GAME_H


