#include <iostream>
#include "threepp/threepp.hpp"
#include "playerHandler.hpp"
#include "playerVisualizer.hpp"
#include "keyInput.hpp"
#include "worldVisualizer.hpp"
#include "cameraAttacher.hpp"
#include "mapFileReader.hpp"
#include "playerCamera.hpp"
#include "raycasters.hpp"
#include "coinVisualizer.hpp"
#include <string>

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();

    auto light = HemisphereLight::create(Color::aliceblue, Color::grey);
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

    auto scene2 = Scene::create();
    scene2->add(scene);

    Vector3 coinPosition{10,10,2};
    CoinVisualizer coinVisualizer{coinPosition};
    scene2->add(coinVisualizer.coin);




    mapFileReader file;
    std::optional<std::string> fileRead = file.read("bin/data/mapdata.txt");

    WorldVisualizer worldVisualizer{1000, 500};

    for (auto& it: file.mapData) {
        worldVisualizer.addBox(it.second.Position,it.second.Size);
    }

    for (const auto& element : worldVisualizer.boxes){
        scene->add(element);
    }
    scene->add(worldVisualizer.flor);

    Raycasters raycasters{10};

    canvas.onWindowResize([&](WindowSize size) {
        cameraVisualizer.camera->aspect = size.getAspect();
        cameraVisualizer.camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        renderer.textHandle(std::to_string(player.getHealth()));

        Vector2 nextMove = keyChecker.getKeyInput();
        raycasters.updateRayCasterDirections(player.getPosition(),keyChecker.getKeyInput(),player.getRotation());
        player.setNextDirection(nextMove.y*dt);
        raycasters.checkMovement(*scene, player.direction_);

        player.move(nextMove.y*dt, -nextMove.x*dt);
        playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);


        cameraCalculations.updateTrailingCamera(player.getPosition(),player.getRotation());
        cameraVisualizer.updateCameraPosition(cameraCalculations.getPosition(), player.quaternion,
                                              cameraCalculations.getCameraAngle());

        renderer.render(scene2, cameraVisualizer.camera);
    });
}