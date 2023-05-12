
#include "game.hpp"
#include <threepp/lights/AmbientLight.hpp>;
#include <threepp/lights/SpotLight.hpp>
#include <threepp/lights/LightShadow.hpp>

Game::Game(float aspect) {

    scene = threepp::Scene::create();

    std::shared_ptr<threepp::AmbientLight> ambientLight = threepp::AmbientLight::create(0xffffff);
    ambientLight->intensity = 0.1f;
    scene->add(ambientLight);

    setSpotLight();

    scene->add(spotLight_);

    playerVisualizer_.setPlayerPosition(player.getPosition(), player.quaternion);
    playerVisualizer_.playerModel->castShadow = true;
    scene->add(playerVisualizer_.playerModel);

    player.setTurnSpeed(2);

    cameraAttacher_ = CameraAttacher(player.getPosition(), player.getRotation());
    cameraAttacher_.setCameraAngle(0);
    cameraAttacher_.setDistanceFromObj(0);
    cameraAttacher_.setCameraHeight(15);

    playerCamera = PlayerCamera(aspect, cameraAttacher_.getCameraAngle(), cameraAttacher_.getPosition());

    scene->add(playerCamera.camera);
    scene->add(worldScene_.layer);
    scene->add(coinLayer_.layer);
    scene->add(spikeLayer_.layer);
}

void Game::running(threepp::Vector3 nextMove, float dt) {

    if (nextMove.z != 1) {

        if (raycasters_.checkForInteractableStep(*coinLayer_.layer)) {
            player.addScore(coinLayer_.coinMath.givePoints());
            coinLayer_.setRandomCoinPosition();
        }

        if (raycasters_.checkForInteractableStep(*spikeLayer_.layer)) {
            player.takeDamage(spikeLayer_.spikeMath_.dealDamage());
        }

        if (player.getHealth() < 0) {
            player.setScore(0);
            player.setHealth(1000);
            player.resetPosAndRotation();
        }

        raycasters_.updateRayCasterDirections(player.getPosition(), nextMove, player.getRotation());
        player.setForceVector(nextMove.y, nextMove.x, dt);
        raycasters_.checkForCollisionStep(*worldScene_.layer, player.direction);

        player.move();
        playerVisualizer_.setPlayerPosition(player.getPosition(), player.quaternion);
        spotLight_->target = playerVisualizer_.playerModel;

        cameraAttacher_.updateTrailingCamera(player.getPosition(), player.getRotation());
        playerCamera.updateCameraPosition(cameraAttacher_.getPosition(), player.quaternion,
                                          cameraAttacher_.getCameraAngle());
    } else {
        player.setScore(0);
        player.position = {0, 0, 2};
    }
}

void Game::setSpotLight() {
    spotLight_ = threepp::SpotLight::create(0xffffff);
    spotLight_->intensity = 0.7f;
    spotLight_->decay = 1;
    spotLight_->castShadow = true;
    spotLight_->shadow->bias = 0.000001f;
    spotLight_->angle = threepp::math::PI / 6;
    spotLight_->distance = 10000;
    spotLight_->position.z = 150;
    spotLight_->shadow->mapSize.set(4096, 4096);
}
