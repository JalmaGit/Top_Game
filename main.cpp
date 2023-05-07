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

using namespace threepp;

void checkForward(){

}

void checkBacwards(){

}

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

    Raycasters raycasters;

    canvas.onWindowResize([&](WindowSize size) {
        cameraVisualizer.camera->aspect = size.getAspect();
        cameraVisualizer.camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        raycasters.updateRayCasterDirection(player.getPosition(),keyChecker.getKeyInput(),player.getRotation());
        raycasters.checkRayCasters(*scene, player.getDirection());
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

        playerVisualizer.getPlayerSize();

        Vector2 nextMove = keyChecker.getKeyInput();

        player.move(nextMove.y*dt, -nextMove.x*dt);
        playerVisualizer.setPlayerPosition(player.getPosition(),player.quaternion);

        cameraCalculations.updateTrailingCamera(player.getPosition(),player.getRotation());
        cameraVisualizer.updateCameraPosition(cameraCalculations.getPosition(), player.quaternion,
                                              cameraCalculations.getCameraAngle());

        std::cout << ", player position" << player.getPosition() << std::endl;

        renderer.render(scene, cameraVisualizer.camera);
    });
}