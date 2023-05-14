#ifndef TOP_GAME_COINMATH_HPP
#define TOP_GAME_COINMATH_HPP

#include <vector>
#include <random>
#include <threepp/math/Vector3.hpp>

class CoinMath {
public:
    threepp::Vector3 position;

    explicit CoinMath();

    [[nodiscard]] int givePoints() const;

    void setPossiblePositions(const std::vector<threepp::Vector3> &newPossiblePositions);

    threepp::Vector3 getNewPosition();

private:

    std::vector<threepp::Vector3> possiblePositions_;
    int points_;
};

#endif //TOP_GAME_COINMATH_HPP
