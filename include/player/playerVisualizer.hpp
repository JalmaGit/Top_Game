#ifndef TOP_GAME_PLAYERVISUALIZER_HPP
#define TOP_GAME_PLAYERVISUALIZER_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/math/Quaternion.hpp>

class PlayerVisualizer {
public:
    std::shared_ptr<threepp::Mesh> playerModel;

    explicit PlayerVisualizer();

    void setPlayerPosition(threepp::Vector3 position, const threepp::Quaternion &rotation) const;

private:

    static std::shared_ptr<threepp::Mesh> playerModelCreation();

};

#endif //TOP_GAME_PLAYERVISUALIZER_HPP
