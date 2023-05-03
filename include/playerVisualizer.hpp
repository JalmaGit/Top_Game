//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_PLAYERVISUALIZER_HPP
#define TOP_GAME_PLAYERVISUALIZER_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include <iostream>

class PlayerVisualizer { //kan dette testes?
public:
    std::shared_ptr<threepp::Mesh> playerModel;

    explicit PlayerVisualizer() {
        playerModel = playerModelCreation();
    }

    auto setPlayerPosition(threepp::Vector3 position, const threepp::Quaternion &rotation) const {
        playerModel->position.copy(position);
        playerModel->rotation.setFromQuaternion(rotation);
    }

private:

    static std::shared_ptr<threepp::Mesh> playerModelCreation();

};

#endif //TOP_GAME_PLAYERVISUALIZER_HPP
