#include <iostream>
#include "threepp/threepp.hpp"
#include "playerHandler.hpp"
#include "playerVisualizer.hpp"
#include "keyInput.hpp"
#include "worldVisualizer.hpp"
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
    playerVisualizer.setPlayerPosition(player.getPosition(),player.rotation);
    scene->add(playerVisualizer.playerModel);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 2000);

    scene->add(camera);

    PlayerCamera cameraCalculations(player.getPosition(), player.getRotation());

    cameraCalculations.setCameraAngle(math::PI/3);
    camera->position = cameraCalculations.getPosition();
    camera->rotateX(cameraCalculations.getCameraAngle());


    Vector3 position1{50,50,2.5};
    Vector3 position2{50,0,2.5};
    std::vector<Vector3> boxes;
    boxes.emplace_back(position1);
    boxes.emplace_back(position2);

    //Make struct that contains position and size of the box.
    //Make unorderedmap

    WorldVisualizer worldVisualizer{1000, 500,boxes};

    for (auto element : worldVisualizer.boxes){
        scene->add(element);
    }

    scene->add(worldVisualizer.flor);

    Raycaster raycaster;

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
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
        playerVisualizer.setPlayerPosition(player.getPosition(),player.rotation);

        cameraCalculations.updateTrailingCamera(player.getPosition(),player.getRotation());
        camera->position = cameraCalculations.getPosition();
        camera->setRotationFromQuaternion(player.rotation);
        camera->rotateX(cameraCalculations.getCameraAngle());

        renderer.render(scene, camera);
    });
}