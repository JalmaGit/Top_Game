//
// Created by Jalma on 06.04.2023.
//

#ifndef TOP_GAME_PLAYER_HPP
#define TOP_GAME_PLAYER_HPP

#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"

class Player : GeometryCreation {
public:
    std::shared_ptr<Mesh> playerModel;
    std::shared_ptr<Mesh> shadowBox;
    std::shared_ptr<PerspectiveCamera> playerCamera;
    Vector3 lastPlayerShadowPos;
    Box3 box3Shadow;

    explicit Player(const Canvas& canvas1){
        playerModel = playerModelCreation();
        shadowBox = shadowBoxCreation();
        lastPlayerShadowPos = shadowBox->position;
        box3Shadow.setFromObject(*shadowBox);
        playerCamera = getCameraCreation(canvas1);
    }

    void moveShadow(std::array<int,2>& direction, float dt) const;

private:
    std::shared_ptr<PerspectiveCamera> getCameraCreation(const Canvas& canvas);

    std::shared_ptr<Mesh> shadowBoxCreation();

    std::shared_ptr<Mesh> playerModelCreation();

};


#endif //TOP_GAME_PLAYER_HPP
