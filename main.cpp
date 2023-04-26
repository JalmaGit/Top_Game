#include <iostream>
#include "threepp/threepp.hpp"
#include "player.hpp"
#include "gameLogic.hpp"
#include "keyInput.hpp"

using namespace threepp;

int main() {



    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();

    KeyChecker keyChecker;

    keyChecker.setKeyInput(canvas);

    Player player{canvas};
    GameLogic gameLogic{canvas, player};

    canvas.onWindowResize([&](WindowSize size) {
        player.playerCamera->aspect = size.getAspect();
        player.playerCamera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        Vector2 vector2 = keyChecker.getKeyInput();

        gameLogic.gameTic(player,dt, vector2);

        renderer.render(gameLogic.scene, player.playerCamera);
    });
}