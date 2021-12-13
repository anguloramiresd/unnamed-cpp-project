//
// Created by dieguin on 12/12/21.
//

#include "Player.h"

Player::Player(const uint16_t pos_x, const uint16_t pos_y) :x(pos_x), y(pos_y){

}

void Player::MovePlayer(uint16_t direction) {
    switch (direction) {
        case R:
            y++;
            break;
        case D:
            x++;
            break;
        case L:
            y--;
            break;
        case U:
            x--;
            break;
        default:
            std::cout<<"Something weird happened\n";
    }
}
