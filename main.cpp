#include <iostream>
#include "threepp/threepp.hpp"
#include "playerHandler.hpp"
#include "playerVisualizer.hpp"
#include "keyInput.hpp"
#include "worldVisualizer.hpp"
#include "playerCamera.hpp"
#include "fileReader.hpp"
#include "cameraVisualizer.hpp"

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

    PlayerCamera cameraCalculations(player.getPosition(), player.getRotation());
    CameraVisualizer cameraVisualizer(canvas.getAspect(),cameraCalculations.getCameraAngle(),cameraCalculations.getPosition());
    scene->add(cameraVisualizer.camera);


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

    Raycaster raycaster;

    canvas.onWindowResize([&](WindowSize size) {
        cameraVisualizer.camera->aspect = size.getAspect();
        cameraVisualizer.camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        raycaster.set(player.getPosition(),player.getDirection());

        auto intersects = raycaster.intersectObjects(scene->children);

        if (!intersects.empty()) {
            auto& intersect = intersects.front();
            std::cout << intersect.distance<< std::endl;
        }

        Vector2 vector2 = keyChecker.getKeyInput();

        player.move(vector2.y*dt, -vector2.x*dt);
        playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);

        cameraCalculations.updateTrailingCamera(player.getPosition(),player.getRotation());
        cameraVisualizer.updateCammeraPosition(cameraCalculations.getPosition(),player.quaternion,cameraCalculations.getCameraAngle());

        renderer.render(scene, cameraVisualizer.camera);
    });
}