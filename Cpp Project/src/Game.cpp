//
// Created by dieguin on 12/12/21.
//

#include "../include/Headers.h"
#include "Game.h"

void Game::Load(sf::Texture &texture, sf::Sprite &sprite, const std::string filename) {
    if (!texture.loadFromFile(filename)) {
        std::cout << "Unable to load\n";
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void Game::Draw(sf::Sprite &sprite, const int &x, const int &y) {
    sprite.setPosition(float(x) * 16, float(y) * 16);
    window_->draw(sprite);
}

Game::Game(const size_t height, const size_t width) {
    height_ = height;
    width_ = width;
    labyrinth_ = new Maze(height, width, 15);
    labyrinth_->Generate();

    window_ = new sf::RenderWindow(sf::VideoMode(width * 16, height * 16 + 40), "Labyrinthical");
    window_->setFramerateLimit(60);

    InitGameInfo();

    Load(cobble_, wall_, "../images/cobble.png");
    Load(dirt_, road_, "../images/dirt.png");
    Load(animal_, sheep_, "../images/sheep.png");
    Load(fruit_, apple_, "../images/apple.png");

    player_ = new Player(1, 1);
}

Game::~Game() {
    delete player_;
    delete window_;
    delete labyrinth_;
}

void Game::Update() {
    while (window_->pollEvent(event_)) {
        switch (event_.type) {
            case sf::Event::Closed:
                window_->close();
                break;

            case sf::Event::KeyPressed:
                if (!win_) {
                    CaptureKey();
                    WasThatAnApple();
                    DidIWin();
                }
                break;

            default:
                break;
        }
    }
    UpdateGameInfo();
}

void Game::Render() {
    window_->clear(sf::Color::White);
    DrawLabyrinth();
    DrawPlayer();
    window_->draw(game_info_);
    window_->display();
}

void Game::Play() {
    clock_.restart();
    while (window_->isOpen()) {
        Update();
        if (win_) {
            ShowWinScreen();
        } else {
            Render();
        }
    }
}

void Game::Draw(const int &x, const int &y) {
    if (labyrinth_->GetCell(y, x) == Maze::kWall) {
        Draw(wall_, x, y);
    } else if (labyrinth_->GetCell(y, x) == Maze::kApple) {
        Draw(apple_, x, y);
    } else {
        Draw(road_, x, y);
    }
}

void Game::DrawLabyrinth() {
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            Draw(j, i);
        }
    }
}

void Game::DrawPlayer() {
    sheep_.setPosition(float(player_->y) * 16, float(player_->x) * 16);
    window_->draw(sheep_);
}

void Game::CaptureKey() {
    switch (event_.key.code) {
        case (sf::Keyboard::A):
            if (labyrinth_->GetCell(player_->x, player_->y - 1) != Maze::kWall) {
                player_->MovePlayer(Player::kL);
            }
            break;
        case (sf::Keyboard::S):
            if (labyrinth_->GetCell(player_->x + 1, player_->y) != Maze::kWall) {
                player_->MovePlayer(Player::kD);
            }
            break;
        case (sf::Keyboard::W):
            if (labyrinth_->GetCell(player_->x - 1, player_->y) != Maze::kWall) {
                player_->MovePlayer(Player::kU);
            }
            break;
        case (sf::Keyboard::D):
            if (labyrinth_->GetCell(player_->x, player_->y + 1) != Maze::kWall) {
                player_->MovePlayer(Player::kR);
            }
            break;
        default:
            break;
    }
}

void Game::WasThatAnApple() {
    if (labyrinth_->GetCell(player_->x, player_->y) == Maze::kApple) {
        labyrinth_->EatApple(player_->x, player_->y);
    }
}

void Game::InitGameInfo() {
    font_.loadFromFile("../fonts/YagiUhfNo2.ttf");
    game_info_.setFont(font_);
    game_info_.setCharacterSize(32);
    game_info_.setPosition(0, height_ * 16);
    game_info_.setFillColor(sf::Color::Black);
    UpdateGameInfo();
}

void Game::UpdateGameInfo() {
    int time = clock_.getElapsedTime().asSeconds();
    game_info_.setString("Apples left: " + std::to_string(labyrinth_->apples_) + " Time: " +
                         std::to_string(time) + " seconds");
}

void Game::DidIWin() {
    win_ = labyrinth_->apples_ == 0;
    win_time_ = clock_.getElapsedTime().asSeconds();
}

void Game::ShowWinScreen() {
    window_->clear(sf::Color::White);
    sf::Text win_text("You won in only " + std::to_string(win_time_) + " seconds", font_, 50);
    win_text.setPosition(width_ / 2, height_ / 2);
    win_text.setFillColor(sf::Color::Black);
    window_->draw(win_text);
    window_->display();
}

