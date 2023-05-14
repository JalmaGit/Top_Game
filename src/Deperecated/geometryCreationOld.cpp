
#include "Deperecated/geometryCreationOld.hpp"

std::shared_ptr<threepp::Mesh> utils::createBox(const threepp::BoxGeometry::Params params, float position) {

    auto boxGeometry = threepp::BoxGeometry::create(params);
    auto boxMaterial = threepp::MeshBasicMaterial::create();
    boxMaterial->color = threepp::Color::skyblue;
    auto box = threepp::Mesh::create(boxGeometry, boxMaterial);
    box->rotateX(threepp::math::PI / 2);
    box->position.z = params.height / 2;
    box->position.x = position;
    return box;
}

std::shared_ptr<threepp::Mesh> utils::createPlane(float x, float y) {
    threepp::TextureLoader loader;

    auto planeGeometry = threepp::PlaneGeometry::create(x, y);
    auto planeMaterial = threepp::MeshBasicMaterial::create();
    planeMaterial->map = loader.load("bin/data/textures/flor.png");
    planeMaterial->side = DoubleSide;
    auto plane = threepp::Mesh::create(planeGeometry, planeMaterial);

    return plane;
}

std::shared_ptr<threepp::Mesh> utils::createStlModel(const std::string &path) {
    threepp::STLLoader stlLoader;
    auto stlGeometry = stlLoader.load(path);
    auto stlMaterial = threepp::MeshPhongMaterial::create();
    stlMaterial->color = Color::grey;
    auto stlModel = threepp::Mesh::create(stlGeometry, stlMaterial);
    stlModel->scale *= 0.2;
    stlModel->rotateX(threepp::math::PI / 2);

    return stlModel;
}
