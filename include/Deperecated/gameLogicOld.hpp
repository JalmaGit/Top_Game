#ifndef TOP_GAME_GAMELOGIC_HPP
#define TOP_GAME_GAMELOGIC_HPP

#include <threepp/threepp.hpp>
#include "playerOld.hpp"
#include "worldOld.hpp"
#include <cmath>

class GameLogic {
public:
    std::shared_ptr<Scene> scene;

    GameLogic(Canvas &canvas, PlayerOld &player) {
        hitBoxDetected = false;

        baseSpeed = 50;

        scene = Scene::create();

        shadowBox = shadowBoxCreation();
        shadowBox->geometry()->computeBoundingSphere();
        lastPlayerShadowPos = shadowBox->position;
        lastPlayerRotation = shadowBox->rotation;

        scene->add(shadowBox);

        scene->add(player.playerCamera);
        scene->add(player.playerModel);


        scene->add(worldGen.boxInWorld);
        scene->add(worldGen.worldFlor);

        light = HemisphereLight::create(Color::aliceblue, Color::grey);
        scene->add(light);

    }

    auto gameTic(PlayerOld &player, float &dt, Vector2 &direction) {

        shadowBox->geometry()->computeBoundingBox();
        box3Shadow.copy(*shadowBox->geometry()->boundingSphere).applyMatrix4(*shadowBox->matrixWorld);

        for (const auto &worldHitBoxes: worldGen.worldHitBoxes) {
            hitBoxDetected = false;
            if (worldHitBoxes.intersectsSphere(box3Shadow)) {
                hitBoxDetected = true;
                break;
            }
        }

        if (!hitBoxDetected) {
            lastPlayerShadowPos = shadowBox->position;

            moveShadow(direction, dt);
        }
        if (hitBoxDetected) {
            shadowBox->position.copy(lastPlayerShadowPos);
        }
        std::cout << hitBoxDetected << std::endl;

        lastPlayerRotation = shadowBox->rotation;
        player.setPlayerPosition(lastPlayerShadowPos, lastPlayerRotation);
    }

private:
    static std::shared_ptr<Mesh> shadowBoxCreation() {
        auto geometry = CylinderGeometry::create(6);
        auto material = MeshBasicMaterial::create();
        auto sphere = Mesh::create(geometry, material);
        sphere->rotateX(math::PI / 2);
        sphere->visible = false;
        return sphere;
    }

    void moveShadow(Vector2 &direction, float dt) {

        if (angle > 2 * math::PI) {
            angle = 0;
        }
        if (angle < 0) {
            angle = 2 * math::PI;
        }

        //Bruke rent enum class eller bruke rent vector2 (vil si enten bruke valg eller matte)
        //bruke direction som vector3 og bare la z være null. prøv med bare en

        shadowBox->position.y += dt * direction.y * baseSpeed * std::cos(angle);
        shadowBox->position.x += dt * direction.y * baseSpeed * std::sin(angle);
        angle -= dt * direction.x;
        shadowBox->rotation.y = -angle;
    }

    float angle{};
    float baseSpeed; //Burde være en tilstand
    std::shared_ptr<HemisphereLight> light;

    Vector3 lastPlayerShadowPos;
    Euler lastPlayerRotation;
    Sphere box3Shadow;
    std::shared_ptr<Mesh> shadowBox;

    WorldGen worldGen{1000, 500};

    bool hitBoxDetected;

};


#endif //TOP_GAME_GAMELOGIC_HPP
