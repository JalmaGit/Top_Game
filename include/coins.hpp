//
// Created by Jalma on 07/05/2023.
//

#ifndef TOP_GAME_COINS_HPP
#define TOP_GAME_COINS_HPP

#include "moveAbleObject.hpp"

class Coin : MoveAble{
public:
    Coin(){
        points_ = 100;
    }

    [[nodiscard]] int givePoints() const{
        return points_;
    }

private:
    int points_;

};


#endif //TOP_GAME_COINS_HPP
