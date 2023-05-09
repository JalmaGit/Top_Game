//
// Created by Jalma on 07/05/2023.
//

#ifndef TOP_GAME_COINMATH_HPP
#define TOP_GAME_COINMATH_HPP

#include "threepp/math/Vector3.hpp"


class CoinMath{
public:
    threepp::Vector3 position;
    explicit CoinMath(){
        points_ = 100;
    }

    [[nodiscard]] int givePoints() const{
        return points_;
    }

    void setPossiblePositions(const std::vector<threepp::Vector3>& newPossiblePositions){
        possiblePositions_ = newPossiblePositions;
    }

    threepp::Vector3 getRandomNewPosition(){
        return possiblePositions_[1];
    }

private:

    std::vector<threepp::Vector3> possiblePositions_;
    int points_;

};


#endif //TOP_GAME_COINMATH_HPP
