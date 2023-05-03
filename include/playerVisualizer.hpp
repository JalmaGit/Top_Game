//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_PLAYERVISUALIZER_HPP
#define TOP_GAME_PLAYERVISUALIZER_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include <iostream>

using namespace threepp;

class PlayerVisualizer { //kan dette testes?
public:
    std::shared_ptr<Mesh> playerModel;

    explicit PlayerVisualizer() {
        playerModel = playerModelCreation();
    }

    auto setPlayerPosition(Vector3 position, const Quaternion &rotation) const {
        playerModel->position.copy(position);
        playerModel->rotation.setFromQuaternion(rotation);
    }

private:

    static std::shared_ptr<Mesh> playerModelCreation();

};

#endif //TOP_GAME_PLAYERVISUALIZER_HPP
