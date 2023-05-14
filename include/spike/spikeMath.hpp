#ifndef TOP_GAME_SPIKEMATH_HPP
#define TOP_GAME_SPIKEMATH_HPP

#include <threepp/math/Vector3.hpp>
#include <vector>

class SpikeMath {
public:
    std::vector<threepp::Vector3> spikePositions;

    explicit SpikeMath();

    void setNewDamage (int newDamage);

    [[nodiscard]] int dealDamage() const;

private:
    int damage_;

};

#endif //TOP_GAME_SPIKEMATH_HPP
