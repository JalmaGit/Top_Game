
#include <threepp/lights/AmbientLight.hpp>
#include <threepp/lights/SpotLight.hpp>
#include <threepp/lights/LightShadow.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>
#include "game.hpp"

Game::Game(float aspect) {

    scene = threepp::Scene::create();

    std::shared_ptr<threepp::AmbientLight> ambientLight = threepp::AmbientLight::create(0xffffff);
    ambientLight->intensity = 0.2f;
    scene->add(ambientLight);

    setSpotLight();
    scene->add(spotLight_);

    player.setTurnSpeed(2.0f);

    playerVisualizer_.setPlayerPosition(player.position, player.quaternion);
    scene->add(playerVisualizer_.playerModel);

    cameraAttacher_ = CameraAttacher(player.getPosition(), player.getRotation());

    playerCamera = PlayerCamera(aspect, cameraAttacher_.getCameraAngle(), cameraAttacher_.getPosition());
    scene->add(playerCamera.camera);

    raycasters_ = Raycasters(7, player.getBaseSpeed());

    scene->add(worldScene_.layer);
    scene->add(coinLayer_.layer);
    scene->add(spikeLayer_.layer);
}

void Game::running(threepp::Vector3 &nextMove, float dt) {

    if (nextMove.z != 1) {

        if (raycasters_.checkForInteractableStep(*coinLayer_.layer)) {
            player.addScore(coinLayer_.coinMath.givePoints());
            coinLayer_.setRandomCoinPosition();
        }

        if (raycasters_.checkForInteractableStep(*spikeLayer_.layer)) {
            player.takeDamage(spikeLayer_.spikeMath.dealDamage());
        }

        if (player.getHealth() <= 200) {
            auto material = dynamic_cast<threepp::MeshPhongMaterial *>(playerVisualizer_.playerModel->material());
            material->color = 0xff0000;
        }

        if (player.getHealth() <= 0) {
            player.setScore(0);
            player.setHealth(1000);
            player.resetPosAndRotation();
            auto material = dynamic_cast<threepp::MeshPhongMaterial*>(playerVisualizer_.playerModel->material());
            material->color = 0x367C2B;
        }

        raycasters_.updateRayCasterDirections(player.position, nextMove, player.getRotation());
        player.setForceVector(nextMove.y, nextMove.x, dt);
        raycasters_.checkForCollisionStep(*worldScene_.layer, player.direction);

        player.move();
        playerVisualizer_.setPlayerPosition(player.position, player.quaternion);
        spotLight_->target = playerVisualizer_.playerModel;

        cameraAttacher_.updateTrailingCamera(player.position, player.getRotation());
        playerCamera.updateCameraPosition(cameraAttacher_.getPosition(), player.quaternion,
                                          cameraAttacher_.getCameraAngle());
    } else {
        player.setScore(0);
        player.resetPosAndRotation();
    }
}

void Game::setSpotLight() {
    spotLight_ = threepp::SpotLight::create(0xffffff);
    spotLight_->intensity = 0.6f;
    spotLight_->decay = 1.0f;
    spotLight_->castShadow = true;
    spotLight_->shadow->bias = 0.000001f;
    spotLight_->angle = threepp::math::PI / 7.0f;
    spotLight_->distance = 10000;
    spotLight_->position.z = 150.0f;
    spotLight_->shadow->mapSize.set(4096.0f * 2.0f, 4096.0f * 2.0f);
}
