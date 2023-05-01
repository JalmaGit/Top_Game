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

    WorldVisualizer worldVisualizer{1000, 500};

    Vector3 box1{50,50,2.5};

    //worldVisualizer.addBox(box1);

    scene->add(worldVisualizer.boxes);
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