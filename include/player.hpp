//
// Created by Jalma on 06.04.2023.
//

#ifndef TOP_GAME_PLAYER_HPP
#define TOP_GAME_PLAYER_HPP

#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"

class Player{
public:
    std::shared_ptr<Mesh> playerModel;
    std::shared_ptr<Mesh> shadowBox;
    std::shared_ptr<Mesh> playerCamera;

    Player(){
        playerModel = playerModelCreation();
        shadowBox = shadowBoxCreation();
    }

    std::shared_ptr<PerspectiveCamera> getCameraCreation(const Canvas& canvas);

private:
    std::shared_ptr<Mesh> shadowBoxCreation();

    std::shared_ptr<Mesh> playerModelCreation();

};


#endif //TOP_GAME_PLAYER_HPP
