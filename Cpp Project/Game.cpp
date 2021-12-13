//
// Created by dieguin on 12/12/21.
//

#include "Headers.h"
#include "Game.h"

Game::Game(const size_t height, const size_t width){
    height_ = height;
    width_ = width;
    labyrinth_ = new Maze(height, width, 15);
    labyrinth_->Generate();

    window_ = new sf::RenderWindow(sf::VideoMode(width*16, height*16+32), "Game");
    window_->setFramerateLimit(60);

    if(!cobble_.loadFromFile("../cobble.png")){
        std::cout<<"Unable to load cobble.png\n";
    }
    wall_.setTexture(cobble_);
    wall_.setTextureRect(sf::IntRect(0,0,16,16));

    if(!dirt_.loadFromFile("../dirt.png")){
        std::cout<<"Unable to load dirt.png";
    }
    road_.setTexture(dirt_);
    road_.setTextureRect(sf::IntRect(0,0,16,16));

    if(!animal_.loadFromFile("../sheep.png")){
        std::cout<<"Unable to load sheep.png";
    }
    sheep_.setTexture(animal_);
    sheep_.setTextureRect(sf::IntRect(0,0,16,16));

    if(!fruit_.loadFromFile("../apple.png")){
        std::cout<<"Unable to load apple.png";
    }
    apple_.setTexture(fruit_);
    apple_.setTextureRect(sf::IntRect(0,0,16,16));

    player_ = new Player(1,1);
}

Game::~Game() {
    delete player_;
    delete window_;
    delete labyrinth_;
}

void Game::Update() {
    while (window_->pollEvent(event_)) {
        switch (event_.type) {
            // window_ closed
            case sf::Event::Closed:
                window_->close();
                break;

                // key pressed
            case sf::Event::KeyPressed:
                CaptureKey();
                WasThatAnApple();
                break;

                // we don't process other types of events
            default:
                break;
        }
    }
}

void Game::Render() {
    window_->clear(sf::Color::White);
    DrawLabyrinth();
    DrawPlayer();
    window_->display();
}

void Game::Play() {
    while (window_->isOpen()) {
        Update();
        Render();
    }
}

void Game::DrawLabyrinth() {
    for (size_t i = 0; i < height_; ++i) {
        for(size_t j = 0; j < width_; ++j){
            if(labyrinth_->GetCell(i,j) == Maze::wall){
                wall_.setPosition(float(j)*16, float(i)*16);
                window_->draw(wall_);
            } else if(labyrinth_->GetCell(i,j) == Maze::apple){
                apple_.setPosition(float(j)*16, float(i)*16);
                window_->draw(apple_);
            } else {
                road_.setPosition(float(j)*16, float(i)*16);
                window_->draw(road_);
            }
        }
    }
}

void Game::DrawPlayer() {
    sheep_.setPosition(float(player_->y)*16, float(player_->x)*16);
    window_->draw(sheep_);
}

void Game::CaptureKey() {
    switch(event_.key.code){
        case(sf::Keyboard::A):
            if(labyrinth_->GetCell(player_->x, player_->y-1) != Maze::wall)
                player_->MovePlayer(Player::L);
            break;
        case(sf::Keyboard::S):
            if(labyrinth_->GetCell(player_->x+1, player_->y) != Maze::wall)
                player_->MovePlayer(Player::D);
            break;
        case(sf::Keyboard::W):
            if(labyrinth_->GetCell(player_->x-1, player_->y) != Maze::wall)
                player_->MovePlayer(Player::U);
            break;
        case(sf::Keyboard::D):
            if(labyrinth_->GetCell(player_->x, player_->y+1) != Maze::wall)
                player_->MovePlayer(Player::R);
            break;
        default:
            break;
    }
}

void Game::WasThatAnApple() {
    if(labyrinth_->GetCell(player_->x, player_->y) == Maze::apple){
        labyrinth_->EatApple(player_->x, player_->y);
    }
}

