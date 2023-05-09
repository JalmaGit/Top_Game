//
// Created by Jalma on 07/05/2023.
//

#ifndef TOP_GAME_SPIKEMATH_HPP
#define TOP_GAME_SPIKEMATH_HPP

#include "threepp/math/Vector3.hpp"

class SpikeMath{
public:
    explicit SpikeMath(){
        damage_ = 100;
    }

    [[nodiscard]] int dealDamage() const{
        return damage_;
    }

private:
    int damage_;

};

#endif //TOP_GAME_SPIKEMATH_HPP
