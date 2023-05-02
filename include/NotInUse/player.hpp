//
// Created by Jalma on 06.04.2023.
//

#ifndef TOP_GAME_PLAYER_HPP
#define TOP_GAME_PLAYER_HPP

#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"
#include <iostream>

class Player { //Make visulizer and the math/movent seperate camera shouldn't be here
    //Splitt out stuff to make each not dependent on each other.
public:
    std::shared_ptr<Mesh> playerModel;

    std::shared_ptr<PerspectiveCamera> playerCamera; //vector3, euler

    explicit Player(const Canvas& canvas1){
        playerModel = playerModelCreation();
        playerCamera = getCameraCreation(canvas1);

    }

    auto setPlayerPosition(Vector3& position, Euler& rotation) const{
        playerModel->position.copy(position);
        playerModel->rotation.copy(rotation);
        playerCamera->position.x = position.x;
        playerCamera->position.y = position.y - 10;
    }

private:
    std::shared_ptr<PerspectiveCamera> getCameraCreation(const Canvas& canvas);

    std::shared_ptr<Mesh> playerModelCreation();

};

#endif //TOP_GAME_PLAYER_HPP
