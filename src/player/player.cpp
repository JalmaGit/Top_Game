
#include "player/player.hpp"

Player::Player(int health) : health_(health) {
    setHealth(health);

    threepp::Vector3 startPosition{0, 0, 2};

    setPosition(startPosition);
    setResetPosition(startPosition);
    score_ = 0;
}

void Player::setHealth(int newHealth) {
    health_ = newHealth;
}

void Player::setScore(int newScore) {
    score_ = newScore;
}

int Player::getHealth() const {
    return health_;
}


int Player::getScore() const {
    return score_;
}

void Player::addScore(int newAddScore) {
    score_ += newAddScore;
}

void Player::removeScore(int newRemoveScore) {
    score_ -= newRemoveScore;
}

void Player::takeDamage(int damage) {
    health_ -= damage;
}

