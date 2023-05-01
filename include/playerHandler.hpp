//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_PLAYERHANDLER_HPP
#define TOP_GAME_PLAYERHANDLER_HPP

#include "moveAbleObject.hpp"
//Ask about this on monday
class Player : public MoveAbleObject {
public:

    explicit Player(int h = 100) : health_(h){
        setHealth(h);
        Vector3 startPosition{0,0,2};
        setPosition(startPosition);
        score_ = 0;
    }

    void setHealth(int newHealth){
        health_ = newHealth;
    }

    void setScore(int newScore){
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

    void removeScore (int newRemoveScore) {
        score_ -= newRemoveScore;
    }

private:
    int health_;
    int score_;
    Vector3 playerSize_;
};


#endif //TOP_GAME_PLAYERHANDLER_HPP
