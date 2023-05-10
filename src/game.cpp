
#include "game.hpp"

Game::Game(float aspect) {

    scene = threepp::Scene::create();

    light = threepp::HemisphereLight::create(0xffffbb, 0x082820);
    light->intensity = 1.0f;

    scene->add(light);

    playerVisualizer.setPlayerPosition(player.getPosition(), player.quaternion);
    scene->add(playerVisualizer.playerModel);

    cameraCalculations = CameraAttacher(player.getPosition(), player.getRotation());
    playerCamera = PlayerCamera(aspect, cameraCalculations.getCameraAngle(), cameraCalculations.getPosition());

    scene->add(playerCamera.camera);
    scene->add(worldScene.layer);
    scene->add(coinLayer.layer);
    scene->add(spikeLayer.layer);
}

void Game::running(threepp::Vector3 nextMove, float dt) {

    if (nextMove.z != 1) {

        if (raycasters.checkForInteractableStep(*coinLayer.layer)) {
            player.addScore(coinLayer.coinMath.givePoints());
            coinLayer.setRandomCoinPosition();
        }

        if (raycasters.checkForInteractableStep(*spikeLayer.layer)) {
            player.takeDamage(spikeLayer.spikeMath_.dealDamage());
        }

        if (player.getHealth() < 0) {
            player.setScore(0);
            player.setHealth(1000);
            player.position = {0, 0, 2};
        }

        raycasters.updateRayCasterDirections(player.getPosition(), nextMove, player.getRotation());
        player.setForceVector(nextMove.y, dt);
        raycasters.checkForCollisionStep(*worldScene.layer, player.direction);

        player.move(-nextMove.x, dt);
        playerVisualizer.setPlayerPosition(player.getPosition(), player.quaternion);

        cameraCalculations.updateTrailingCamera(player.getPosition(), player.getRotation());
        playerCamera.updateCameraPosition(cameraCalculations.getPosition(), player.quaternion,
                                          cameraCalculations.getCameraAngle());
    } else {
        player.setScore(0);
        player.position = {0, 0, 2};
    }
}
