#include <iostream>
#include "threepp/threepp.hpp"
#include "playerHandler.hpp"
#include "playerVisualizer.hpp"
#include "keyInput.hpp"
#include "world.hpp"

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 2000);

    scene->add(camera);
    camera->position.z = 25;
    camera->position.y;
    camera->rotateX(math::PI/4);


    //OrbitControls controls{camera, canvas};

    auto light = HemisphereLight::create(Color::aliceblue, Color::grey);
    scene->add(light);

    KeyChecker keyChecker;

    keyChecker.setKeyInput(canvas);

   // Raycaster raycaster;


    Player player;
    PlayerVisualizer playerVisualizer;
    playerVisualizer.setPlayerPosition(player.getPosition(),player.rotation);
   // raycaster.set(player.getPosition(),player.getRotation();
    scene->add(playerVisualizer.playerModel);

    WorldGen worldGen{1000,500};

    scene->add(worldGen.boxInWorld);
    scene->add(worldGen.worldFlor);


    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        Vector2 vector2 = keyChecker.getKeyInput();

        player.move(vector2.y*dt, -vector2.x*dt);
        playerVisualizer.setPlayerPosition(player.getPosition(),player.rotation);
        Vector3 direction {std::sin(player.getRotation()), std::cos(player.getRotation()), -1};
        direction *= -5;
        std::cout << direction << std::endl;
        camera->position = player.getPosition()+direction;
        camera->setRotationFromQuaternion(player.rotation);
        camera->rotateX(math::PI/3);

        renderer.render(scene, camera);
    });
}