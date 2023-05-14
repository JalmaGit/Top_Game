
#include "Deperecated//playerOld.hpp"

std::shared_ptr<threepp::Mesh> Player::playerModelCreation() {
    std::string path = "bin/data/models/stl/mogus.stl";
    std::shared_ptr<threepp::Mesh> model = utils::createStlModel(path);

    return model;
}

std::shared_ptr<threepp::PerspectiveCamera> Player::getCameraCreation(const threepp::Canvas &canvas) {
    std::shared_ptr<threepp::PerspectiveCamera> camera = threepp::PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 2000);
    camera->position.z = 50;
    camera->position.y = -10;
    camera->rotation.x = threepp::math::PI / 6;

    return camera;
}

