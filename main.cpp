#include <iostream>
#include "threepp/threepp.hpp"
#include "playerHandler.hpp"
#include "playerVisualizer.hpp"
#include "keyInput.hpp"
#include "worldScene.hpp"
#include "cameraAttacher.hpp"
#include "playerCamera.hpp"
#include "raycasters.hpp"
#include "coinVisualizer.hpp"
#include "spikeVisualizer.hpp"
#include "coinMath.hpp"
#include <string>

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};
    renderer.shadowMap().enabled = true;

    auto scene = Scene::create();

    KeyChecker keyChecker;
    keyChecker.setKeyInput(canvas);

    Player player;
    PlayerVisualizer playerVisualizer;
    playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);
    scene->add(playerVisualizer.playerModel);

    CameraAttacher cameraCalculations(player.getPosition(), player.getRotation());
    PlayerCamera cameraVisualizer(canvas.getAspect(), cameraCalculations.getCameraAngle(), cameraCalculations.getPosition());
    scene->add(cameraVisualizer.camera);

    WorldScene worldScene;
    scene->add(worldScene.scene);

    Raycasters raycasters{7};
    renderer.enableTextRendering();
    auto &textHandler = renderer.textHandle();

    auto scene2 = Scene::create();
    scene2->add(scene);

    auto scene3 = Scene::create();
    Vector3 coinPosition{10,10,2};
    CoinMath coinMath{coinPosition};
    CoinVisualizer coinVisualizer{coinMath.position};
    scene3->add(coinVisualizer.coin);

    Vector3 spikePosition{-10,-10,0};
    SpikeVisualizer spikeVisualizer{spikePosition};
    scene3->add(spikeVisualizer.spike);

    scene2->add(scene3);

    canvas.onWindowResize([&](WindowSize size) {
        cameraVisualizer.camera->aspect = size.getAspect();
        cameraVisualizer.camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandler.scale = size.getAspect();
    });


    canvas.animate([&](float dt) {


        Vector3 nextMove = keyChecker.getKeyInput();

        if (nextMove.z != 1){
            textHandler.setText(std::to_string(player.getScore()));

            if(raycasters.checkForInteractable(*scene3)){
                player.addScore(coinMath.givePoints());
            }

            raycasters.updateRayCasterDirections(player.getPosition(),keyChecker.getKeyInput(),player.getRotation());
            player.setNextDirection(nextMove.y,dt);
            raycasters.checkForWalls(*worldScene.scene, player.direction_);

            player.move(-nextMove.x, dt);
            playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);

            cameraCalculations.updateTrailingCamera(player.getPosition(),player.getRotation());
            cameraVisualizer.updateCameraPosition(cameraCalculations.getPosition(), player.quaternion,
                                                  cameraCalculations.getCameraAngle());
        } else {
            player.setScore(0);
            player.position = {0,0,2};
        }


        renderer.render(scene2, cameraVisualizer.camera);
    });
}