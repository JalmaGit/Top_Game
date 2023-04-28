//
// Created by Jalma on 19.04.2023.
//

#ifndef TOP_GAME_GAMELOGIC_HPP
#define TOP_GAME_GAMELOGIC_HPP

#include "threepp/threepp.hpp"
#include "player.hpp"
#include "world.hpp"
#include <cmath>

class GameLogic {
public:
    std::shared_ptr<Scene> scene;

    GameLogic(Canvas &canvas, Player &player) {
        hitBoxDetected = false;

        baseSpeed = 50;

        scene = Scene::create();

        shadowBox = shadowBoxCreation();
        lastPlayerShadowPos = shadowBox->position;
        lastPlayerRotation = shadowBox->rotation;

        box3Shadow.setFromObject(*shadowBox);
        scene->add(shadowBox);

        const auto box3Helper = Box3Helper::create(box3Shadow);
        box3Helper->position.setY(1);
        scene->add(box3Helper);

        scene->add(player.playerCamera);
        scene->add(player.playerModel);


        scene->add(worldGen.boxInWorld);
        scene->add(worldGen.worldFlor);

        light = HemisphereLight::create(Color::aliceblue, Color::grey);
        scene->add(light);

    }

    auto gameTic(Player &player, float &dt, Vector2& direction) {

        shadowBox->geometry()->computeBoundingBox();
        Matrix4 matrix4;
        matrix4.makeRotationFromEuler(shadowBox->rotation);
        box3Shadow.applyMatrix4(matrix4);
        box3Shadow.copy(*shadowBox->geometry()->boundingBox).applyMatrix4(*shadowBox->matrixWorld);


        for (const auto & worldHitBoxes : worldGen.worldHitBoxes) {
            hitBoxDetected = false;
            if (worldHitBoxes.intersectsBox(box3Shadow)) {
                hitBoxDetected = true;
                break;
            }
        }

        if (!hitBoxDetected) {
            lastPlayerShadowPos = shadowBox->position;
            lastPlayerRotation = shadowBox->rotation;
            moveShadow(direction, dt);
        }
        if (hitBoxDetected) {
            shadowBox->position.copy(lastPlayerShadowPos);
            shadowBox->rotation.copy(lastPlayerRotation);
        }
        std::cout << hitBoxDetected << std::endl;

        player.setPlayerPosition(lastPlayerShadowPos, lastPlayerRotation);
    }

private:
    static std::shared_ptr<Mesh> shadowBoxCreation() {
        std::string path = "bin/data/models/stl/mogus.stl";
        std::shared_ptr<Mesh> shadow = utils::createStlModel(path);
        shadow->visible = false;
        return shadow;
    }

    void moveShadow(Vector2& direction, float dt) {

        if (angle > 2*math::PI){
            angle = 0;
        }
        if (angle < 0){
            angle = 2*math::PI;
        }

        //Bruke rent enum class eller bruke rent vector2 (vil si enten bruke valg eller matte)
        //bruke direction som vector3 og bare la z være null. prøv med bare en

        if (direction.y == utils::UP){
            shadowBox->position.y += dt*baseSpeed*std::cos(angle);
            shadowBox->position.x += dt*baseSpeed*std::sin(angle);
        }
        if (direction.y == utils::DOWN){ //Re think direction
            shadowBox->position.y -= dt*baseSpeed*std::cos(angle);
            shadowBox->position.x -= dt*baseSpeed*std::sin(angle);
        }
        if(direction.x == utils::LEFT || direction.x == utils::RIGHT){
            angle = dt;
        }
        //if(){
        //    angle += dt;
        //}
        shadowBox->rotation.y = -angle;
    }

    float angle{};
    float baseSpeed; //Burde være en tilstand
    std::shared_ptr<HemisphereLight> light;

    Vector3 lastPlayerShadowPos;
    Euler lastPlayerRotation;
    Box3 box3Shadow;
    std::shared_ptr<Mesh> shadowBox;

    WorldGen worldGen{1000, 500};

    bool hitBoxDetected;

};


#endif //TOP_GAME_GAMELOGIC_HPP
