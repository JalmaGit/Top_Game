//
// Created by Jalma on 07/05/2023.
//

#ifndef TOP_GAME_MINES_HPP
#define TOP_GAME_MINES_HPP

#include "moveAbleObject.hpp"

class Spike : MoveAble{
public:
    Spike(){
        damage_ = 100;
    }

    [[nodiscard]] int dealDamage() const{
        return damage_;
    }

private:
    int damage_;

};

#endif //TOP_GAME_MINES_HPP
