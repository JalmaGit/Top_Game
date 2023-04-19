//
// Created by Jalma on 19.04.2023.
//

#ifndef TOP_GAME_GAMELOGIC_HPP
#define TOP_GAME_GAMELOGIC_HPP

#include "threepp/threepp.hpp"
#include "player.hpp"
#include "world.hpp"
#include "keyInput.hpp"

void runGameLogic(Player& player, WorldGen& worldGen, bool& hitBoxDetected, Vector3& lastPlayerShadowPos, KeyChecker& keyChecker, float& dt){

    std::array<int,2> direction{0,0};

    player.shadowBox->geometry()->computeBoundingBox();
    player.box3Shadow.copy(*player.shadowBox->geometry()->boundingBox).applyMatrix4(*player.shadowBox->matrixWorld);


    for (int i{}; i < worldGen.worldHitBoxes.size(); i++) {
        if (worldGen.worldHitBoxes[i].intersectsBox(player.box3Shadow)) {
            hitBoxDetected = true;
            break;

        } else {
            hitBoxDetected = false;
        }
    }

    keyChecker.getKeyInput(direction);

    if (!hitBoxDetected) {
        lastPlayerShadowPos = player.shadowBox->position;
        player.moveShadow(direction, dt);
    }
    if (hitBoxDetected) {
        player.shadowBox->position.copy(lastPlayerShadowPos);
    }
    player.playerModel->position.copy(lastPlayerShadowPos);
    player.playerCamera->position.x = lastPlayerShadowPos.x;
    player.playerCamera->position.y = lastPlayerShadowPos.y - 10;
}



#endif //TOP_GAME_GAMELOGIC_HPP
