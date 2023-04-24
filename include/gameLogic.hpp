//
// Created by Jalma on 19.04.2023.
//

#ifndef TOP_GAME_GAMELOGIC_HPP
#define TOP_GAME_GAMELOGIC_HPP

#include "threepp/threepp.hpp"
#include "player.hpp"
#include "world.hpp"
#include "keyInput.hpp"

class GameLogic {
public:
    std::shared_ptr<Scene> scene;

    GameLogic(Canvas &canvas, Player &player) {
        hitBoxDetected = false;

        scene = Scene::create();

        scene->add(player.playerCamera);
        scene->add(player.playerModel);
        scene->add(player.shadowBox);

        scene->add(worldGen.boxInWorld);
        scene->add(worldGen.worldFlor);

        keyChecker.setKeyInput(canvas);

        light = HemisphereLight::create(Color::aliceblue, Color::grey);
        scene->add(light);
    }

    void gameTic(Player &player, float &dt) {

        std::array<int, 2> direction{0, 0};

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

private:
    WorldGen worldGen{1000, 500};
    KeyChecker keyChecker;
    bool hitBoxDetected;
    std::shared_ptr<HemisphereLight> light;
};


#endif //TOP_GAME_GAMELOGIC_HPP
