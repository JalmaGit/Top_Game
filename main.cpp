#include <iostream>
#include <string>
#include <threepp/Canvas.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/math/Vector3.hpp>
#include "keyInput.hpp"
#include "game.hpp"


using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().vsync(false).antialiasing(16)};
    GLRenderer renderer{canvas};
    renderer.shadowMap().enabled = true;
    renderer.shadowMap().type = PCFSoftShadowMap;

    Game game(canvas.getAspect());

    KeyChecker keyChecker;
    keyChecker.setKeyInput(canvas);

    renderer.enableTextRendering();
    auto &textHandler = renderer.textHandle();

    canvas.onWindowResize([&](WindowSize size) {
        game.playerCamera.camera->aspect = size.getAspect();
        game.playerCamera.camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandler.scale = size.getAspect();
    });


    canvas.animate([&](float dt) -> void {

        Vector3 nextMove = keyChecker.getKeyInput();

        textHandler.setText(std::to_string(game.player.getScore()));

        game.running(nextMove,dt);

        renderer.render(game.scene, game.playerCamera.camera);
    });
}