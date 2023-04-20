//
// Created by Jalma on 19.04.2023.
//

#ifndef TOP_GAME_GAMELOGIC_HPP
#define TOP_GAME_GAMELOGIC_HPP

#include "threepp/threepp.hpp"
#include "player.hpp"
#include "world.hpp"
#include "keyInput.hpp"

class GameLogic{
public:
        Vector3 lastPlayerShadowPos;
        bool hitBoxDetected;
    explicit GameLogic(Player& player, WorldGen& worldGen, KeyChecker& keyChecker){
        lastPlayerShadowPos = player.shadowBox->position;
        hitBoxDetected = false;
    }
    
private:
};

void runGameLogic(Player& player, WorldGen& worldGen, bool& hitBoxDetected, KeyChecker& keyChecker, float& dt){

    //Spøre lærer om det det er verdt det å lage en game logic klasse.

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
        player.lastPlayerShadowPos = player.shadowBox->position;
        player.moveShadow(direction, dt);
    }
    if (hitBoxDetected) {
        player.shadowBox->position.copy(player.lastPlayerShadowPos);
    }
    player.playerModel->position.copy(player.lastPlayerShadowPos);
    player.playerCamera->position.x = player.lastPlayerShadowPos.x;
    player.playerCamera->position.y = player.lastPlayerShadowPos.y - 10;
}



#endif //TOP_GAME_GAMELOGIC_HPP
