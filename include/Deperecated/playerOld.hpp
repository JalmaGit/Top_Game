#ifndef TOP_GAME_PLAYEROLD_HPP
#define TOP_GAME_PLAYEROLD_HPP

#include <threepp/threepp.hpp>
#include <iostream>

#include "geometryCreationOld.hpp"

class PlayerOld {
public:
    std::shared_ptr<Mesh> playerModel;

    std::shared_ptr<PerspectiveCamera> playerCamera; //vector3, euler

    explicit PlayerOld(const Canvas &canvas1) {
        playerModel = playerModelCreation();
        playerCamera = getCameraCreation(canvas1);

    }

    auto setPlayerPosition(Vector3 &position, Euler &rotation) const {
        playerModel->position.copy(position);
        playerModel->rotation.copy(rotation);
        playerCamera->position.x = position.x;
        playerCamera->position.y = position.y - 10;
    }

private:
    std::shared_ptr<PerspectiveCamera> getCameraCreation(const Canvas &canvas);

    std::shared_ptr<Mesh> playerModelCreation();
};

#endif //TOP_GAME_PLAYEROLD_HPP
