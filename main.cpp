#include <iostream>
#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"
#include "world.hpp"
#include "player.hpp"
#include "keyInput.hpp"

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};
    auto scene = Scene::create();

    //Used to help with visualization
    //OrbitControls controls{camera, canvas};

    KeyChecker keyChecker;
    keyChecker.setKeyInput(canvas);

    auto light = HemisphereLight::create(Color::aliceblue, Color::grey);
    scene->add(light);

    Player player{canvas};
    scene->add(player.playerCamera);
    scene->add(player.playerModel);
    scene->add(player.shadowBox);

    WorldGen worldGen{1000,500};
    scene->add(worldGen.worldFlor);
    scene->add(worldGen.getBox());

    Box3 box3;
    box3.setFromObject(*worldGen.getBox());


    canvas.onWindowResize([&](WindowSize size) {
        player.playerCamera->aspect = size.getAspect();
        player.playerCamera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    auto lastPlayerShadowPos = player.shadowBox->position;
    bool hitBoxDetected{false};

    canvas.animate([&](float dt) {

        std::cout << dt << std::endl;

        std::array<int,2> direction{0,0};

        player.shadowBox->geometry()->computeBoundingBox();
        player.box3Shadow.copy(*player.shadowBox->geometry()->boundingBox).applyMatrix4(*player.shadowBox->matrixWorld);

        for (int i{}; i < worldGen.worldWallHitBox.size(); i++) {
            if (worldGen.worldWallHitBox[i].intersectsBox(player.box3Shadow)) {
                hitBoxDetected = true;
                break;

            } else {
                hitBoxDetected = false;
            }
        }

        if (!hitBoxDetected) {
            if (box3.intersectsBox(player.box3Shadow)) {
                hitBoxDetected= true;
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

        renderer.render(scene, player.playerCamera);
    });
}
