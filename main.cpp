#include <iostream>
#include "threepp/threepp.hpp"
#include "player.hpp"
#include "gameLogic.hpp"

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    Player player{canvas};

    GameLogic gameLogic{canvas, player};

    canvas.onWindowResize([&](WindowSize size) {
        player.playerCamera->aspect = size.getAspect();
        player.playerCamera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        gameLogic.gameTic(player,dt);

        renderer.render(gameLogic.scene, player.playerCamera);
    });
}