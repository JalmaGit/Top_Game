//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_PLAYEROLD_HPP
#define TOP_GAME_PLAYER_HPP

#include "moveAble.hpp" //Make Headerfile same name as class

class Player : public MoveAble {
public:

    explicit Player(int health = 1000) : health_(health) {
        setHealth(health);
        threepp::Vector3 startPosition{0, 0, 2};
        setPosition(startPosition);
        score_ = 0;
    }

    void setHealth(int newHealth) {
        health_ = newHealth;
    }

    void setScore(int newScore) {
        score_ = newScore;
    }

    [[nodiscard]] int getHealth() const {
        return health_;
    }

    [[nodiscard]] int getScore() const {
        return score_;
    }

    void addScore(int newAddScore) {
        score_ += newAddScore;
    }

    void removeScore(int newRemoveScore) {
        score_ -= newRemoveScore;
    }

    void takeDamage(int damage) {
        health_ -= damage;
    }

private:
    int health_;
    int score_;
    threepp::Vector3 playerSize_;
};

#endif //TOP_GAME_PLAYEROLD_HPP
