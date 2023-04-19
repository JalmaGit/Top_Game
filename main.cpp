#include <iostream>
#include <vector>
#include "threepp/threepp.hpp"
#include "world.hpp"
#include "player.hpp"
#include "keyInput.hpp"
#include "gameLogic.hpp"

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};
    auto scene = Scene::create();

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
    scene->add(worldGen.boxInWorld);

    canvas.onWindowResize([&](WindowSize size) {
        player.playerCamera->aspect = size.getAspect();
        player.playerCamera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    auto lastPlayerShadowPos = player.shadowBox->position;
    bool hitBoxDetected{false};

    std::vector<int> hello;
    hello.emplace_back(4);
    hello.emplace_back(5);

    std::cout << hello.size() << std::endl;
    std::cout << hello[0] << std::endl;

    canvas.animate([&](float dt) {

        runGameLogic(player,worldGen,hitBoxDetected,lastPlayerShadowPos,keyChecker, dt);

        renderer.render(scene, player.playerCamera);
    });
}
