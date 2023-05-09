#include <iostream>
#include "threepp/threepp.hpp"
#include "player/player.hpp"
#include "player/playerVisualizer.hpp"
#include "keyInput.hpp"
#include "world/worldLayer.hpp"
#include "player/cameraAttacher.hpp"
#include "player/playerCamera.hpp"
#include "raycasters.hpp"
#include "coin/coinLayer.hpp"
#include "spike/spikeLayer.hpp"
#include "coin/coinMath.hpp"
#include "game.hpp"
#include <string>

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();

    auto light = threepp::HemisphereLight::create(0xffffbb, 0x082820);
    light->intensity = 1.0f;
    scene->add(light);

    KeyChecker keyChecker;
    keyChecker.setKeyInput(canvas);

    Player player;
    PlayerVisualizer playerVisualizer;
    playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);
    scene->add(playerVisualizer.playerModel);

    CameraAttacher cameraCalculations(player.getPosition(), player.getRotation());
    PlayerCamera cameraVisualizer(canvas.getAspect(), cameraCalculations.getCameraAngle(), cameraCalculations.getPosition());
    scene->add(cameraVisualizer.camera);

    WorldLayer worldScene;
    scene->add(worldScene.layer);

    Raycasters raycasters{7};

    CoinLayer coinLayer;

    scene->add(coinLayer.layer);

    SpikeLayer spikeLayer;
    scene->add(spikeLayer.layer);

    renderer.enableTextRendering();
    auto &textHandler = renderer.textHandle();

    canvas.onWindowResize([&](WindowSize size) {
        cameraVisualizer.camera->aspect = size.getAspect();
        cameraVisualizer.camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandler.scale = size.getAspect();
    });


    canvas.animate([&](float dt) {


        Vector3 nextMove = keyChecker.getKeyInput();

        textHandler.setText(std::to_string(player.getScore()));
        std::cout << player.getHealth() << std::endl;

        if (nextMove.z != 1){
            textHandler.setText(std::to_string(player.getScore()));
            std::cout << player.getHealth() << std::endl;

            if(raycasters.checkForInteractableStep(*coinLayer.layer)){
                player.addScore(100);
                coinLayer.setRandomCoinPosition();
            }

            if(raycasters.checkForInteractableStep(*spikeLayer.layer)){
                player.takeDamage(spikeLayer.spikeMath_.dealDamage());
            }

            if(player.getHealth() < 0){
                player.setScore(0);
                player.setHealth(1000);
                player.position = {0,0,2};
            }

            raycasters.updateRayCasterDirections(player.getPosition(),keyChecker.getKeyInput(),player.getRotation());
            player.setForceVector(nextMove.y, dt);
            raycasters.checkForCollisionStep(*worldScene.layer, player.direction);

            player.move(-nextMove.x, dt);
            playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);

            cameraCalculations.updateTrailingCamera(player.getPosition(),player.getRotation());
            cameraVisualizer.updateCameraPosition(cameraCalculations.getPosition(), player.quaternion,
                                                  cameraCalculations.getCameraAngle());
        } else {
            player.setScore(0);
            player.position = {0,0,2};
        }


        renderer.render(scene, cameraVisualizer.camera);
    });
}