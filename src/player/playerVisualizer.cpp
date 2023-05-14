
#include <player/playerVisualizer.hpp>
#include <threepp/extras/core/Shape.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>
#include <threepp/math/MathUtils.hpp>
#include <threepp/loaders/STLLoader.hpp>

PlayerVisualizer::PlayerVisualizer() {
    playerModel = playerModelCreation();
}

void PlayerVisualizer::setPlayerPosition(
        threepp::Vector3 &position, const threepp::Quaternion &rotation) const {
    playerModel->position.copy(position);
    playerModel->rotation.setFromQuaternion(rotation);
}

std::shared_ptr<threepp::Mesh> PlayerVisualizer::playerModelCreation() {
    threepp::STLLoader stlLoader;

    auto stlGeometry = stlLoader.load("data/Tractor.stl");
    stlGeometry->rotateX(threepp::math::PI / 2);
    stlGeometry->center();

    auto stlMaterial = threepp::MeshPhongMaterial::create();
    stlMaterial->color = 0x367C2B;

    auto stlModel = threepp::Mesh::create(stlGeometry, stlMaterial);
    stlModel->scale *= 0.045;
    stlModel->castShadow = true;
    stlModel->receiveShadow = true;

    return stlModel;
}



