#include <iostream>
#include "threepp/threepp.hpp"
#include "playerHandler.hpp"
#include "playerVisualizer.hpp"
#include "keyInput.hpp"
#include "worldVisualizer.hpp"
#include "cameraAttacher.hpp"
#include "mapFileReader.hpp"
#include "playerCamera.hpp"

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
     /*
        if(w == 1) {
            if(checkForward){
                player.move(vector2.y*dt,-vector2.x*dt);
            }
        }
        if(s == -1) {
            if(checkBackward){
                player.move(vector2.y*dt,-vector2.x*dt);
            }
        }
        if(d == 1){
            if(check){
                player.move(vector2.y*dt,-vector2.x*dt);
            }
        }
        if(a == 1){
            if(check){
                player.move(vector2.y*dt,-vector2.x*dt);
            }
        }

*/
        Vector2 vector2 = keyChecker.getKeyInput();

        player.move(vector2.y*dt, -vector2.x*dt);
        playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);

        cameraCalculations.updateTrailingCamera(player.getPosition(),player.getRotation());
        cameraVisualizer.updateCameraPosition(cameraCalculations.getPosition(), player.quaternion,
                                              cameraCalculations.getCameraAngle());

        renderer.render(scene, cameraVisualizer.camera);
    });
}