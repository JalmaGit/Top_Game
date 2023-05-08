//
// Created by Jalma on 07/05/2023.
//

#ifndef TOP_GAME_COINMATH_HPP
#define TOP_GAME_COINMATH_HPP

#include <threepp/math/Vector3.hpp>

class CoinMath{
public:
    threepp::Vector3 position;
    explicit CoinMath(threepp::Vector3 newPosition){
        points_ = 100;
        position = newPosition;
    }

    [[nodiscard]] int givePoints() const{
        return points_;
    }

private:
    int points_;

};


#endif //TOP_GAME_COINMATH_HPP
