//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_PLAYERVISUALIZER_HPP
#define TOP_GAME_PLAYERVISUALIZER_HPP

#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"
#include <iostream>

class Player { //Make visulizer and the math/movent seperate camera shouldn't be here
    //Splitt out stuff to make each not dependent on each other.
public:
    std::shared_ptr<Mesh> playerModel; //Make vector3, euler

    // Matrix4 matrix4;
    // Quaternion quaternion; //Look into this instead of euler

    std::shared_ptr<PerspectiveCamera> playerCamera; //vector3, euler

    explicit Player(const Canvas& canvas1){
        playerModel = playerModelCreation();
        playerCamera = getCameraCreation(canvas1);  //Doesn't need to know.
        // matrix4.setPosition(vector3); try and work with this

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

#endif //TOP_GAME_PLAYERVISUALIZER_HPP
