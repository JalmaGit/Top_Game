#include <iostream>
#include <string>
#include <threepp/Canvas.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/math/Vector3.hpp>
#include "keyInput.hpp"
#include "game.hpp"
#include <threepp/core/Clock.hpp>


using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters()
    .vsync(false)
    .antialiasing(16)
    .title("TOP GAME!!!")
    .favicon("data/topGameLogo.png")};

    GLRenderer renderer{canvas};
    renderer.shadowMap().enabled = true;
    renderer.shadowMap().type = PCFSoftShadowMap;

    Game game(canvas.getAspect());

    KeyChecker keyChecker;
    keyChecker.setKeyInput(canvas);

    renderer.enableTextRendering();
    auto &textHandlerForScore = renderer.textHandle();
    auto &textHandlerForHealth = renderer.textHandle();
    textHandlerForHealth.setPosition(0,20);

    canvas.onWindowResize([&](WindowSize size) {
        game.playerCamera.camera->aspect = size.getAspect();
        game.playerCamera.camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandlerForScore.scale = size.getAspect();
        textHandlerForHealth.setPosition(0,size.height/20);
        textHandlerForHealth.scale = size.getAspect();
    });
    
    Clock clock;
    canvas.animate([&]()  {
        float dt = clock.getDelta();

        Vector3 nextMove = keyChecker.getKeyInput();

        textHandlerForScore.setText("Score: " + std::to_string(game.player.getScore()));
        textHandlerForHealth.setText("Health: " + std::to_string(game.player.getHealth()));

        game.running(nextMove,dt);

        renderer.render(game.scene, game.playerCamera.camera);
    });
}