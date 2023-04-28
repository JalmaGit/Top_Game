//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_PLAYERHANDLER_HPP
#define TOP_GAME_PLAYERHANDLER_HPP

#include "moveAbleObject.hpp"

class Player : public MoveAbleObject {
public:

    explicit Player(int h = 100, float b = 50 , float t = 1) : health_(h), baseSpeed_(b), turnSpeed_(t) {
        setHealth(h);
        score_ = 0; //Ask about this on monday
        setBaseSpeed(b);
        setTurnSpeed(t);
        playerSize_ = {10,10,100};
    }

    void setHealth(int newHealth){
        health_ = newHealth;
    }

    void setScore(int newScore){
        score_ = newScore;
    }

    void setBaseSpeed(float newBaseSpeed){
        baseSpeed_ = newBaseSpeed;
    }

    void setTurnSpeed(float newTurnSpeed){
        turnSpeed_ = newTurnSpeed;
    }

    [[nodiscard]] int getHealth() const {
        return health_;
    }

    [[nodiscard]] int getScore() const {
        return score_;
    }

    [[nodiscard]] float getBaseSpeed() const{
        return baseSpeed_;
    }

    [[nodiscard]] float getTurnSpeed() const {
        return turnSpeed_;
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
    float baseSpeed_;
    float turnSpeed_;
    Vector3 playerSize_;
};


#endif //TOP_GAME_PLAYERHANDLER_HPP
