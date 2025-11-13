//
// Created by tomgi on 03/11/2025.
//

#include "../Header/Player.h"

Player::Player(const std::string &name, const std::string &color, const std::string &colorCode, int &exchangecoupon) {
    this-> playerName = name;
    this-> playerColor = color;
    this-> playerColorCode = colorCode;
    this-> TileExchangeCoupon = exchangecoupon;
}

Player::~Player(){}

std::string Player::getName() {
    return this->playerName;
}

std::string Player::getColor() {
    return this->playerColor;
}

std::string Player::getColorCode() {
    return this->playerColorCode;
}

int Player::getTileExchangeCoupon() const {
    return this->TileExchangeCoupon;
}

void Player::setExchangeCoupon(int exchangeCoupon) {
    this->TileExchangeCoupon = exchangeCoupon;
}
