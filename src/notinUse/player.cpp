//
// Created by Jalma on 06.04.2023.
//

#include "NotInUse/player.hpp"
#include <iostream>

std::shared_ptr<Mesh> Player::playerModelCreation() {
    std::string path = "bin/data/models/stl/mogus.stl";
    std::shared_ptr<Mesh> model = utils::createStlModel(path);
    return model;
}

std::shared_ptr<PerspectiveCamera> Player::getCameraCreation(const Canvas &canvas) {
    std::shared_ptr<PerspectiveCamera> camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 2000);
    camera->position.z = 50;
    camera->position.y = -10;
    camera->rotation.x = math::PI / 6;
    return camera;
}

