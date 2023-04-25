//
// Created by Jalma on 06.04.2023.
//

#include "player.hpp"
#include <iostream>

std::shared_ptr<Mesh> Player::shadowBoxCreation() {
    std::string path = "bin/data/models/stl/mogus.stl";
    std::shared_ptr<Mesh> shadow = createStlModel(path);
    shadow->visible = false;
    return shadow;
}

std::shared_ptr<Mesh> Player::playerModelCreation() {
    std::string path = "bin/data/models/stl/mogus.stl";
    std::shared_ptr<Mesh> model = createStlModel(path);
    return model;
}

std::shared_ptr<PerspectiveCamera> Player::getCameraCreation(const Canvas &canvas) {
    std::shared_ptr<PerspectiveCamera> camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 2000);
    camera->position.z = 50;
    camera->position.y = -10;
    camera->rotation.x = math::PI / 6;
    return camera;
}

void Player::moveShadow(std::array<int, 2> &direction, float dt) const {

    float baseSpeed{50}; //Burde være en tilstand

    shadowBox->position.y += static_cast<float>(direction[0]) * dt * baseSpeed;
    shadowBox->position.x += static_cast<float>(direction[1]) * dt * baseSpeed;

    if (direction[0] == 1 || direction[0] == -1) {
        playerModel->rotation.y = static_cast<float>(direction[0])*math::PI/2 + 3*math::PI/2;
    }
    if (direction[1] == 1 || direction[1] == -1) {
        playerModel->rotation.y = -static_cast<float>(direction[1])*math::PI / 2;
    }
}

