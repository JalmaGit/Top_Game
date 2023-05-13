
#include "spike/spikeVisualizer.hpp"

std::shared_ptr<threepp::Mesh> SpikeVisualizer::createSpike(threepp::Vector3 position) {
    auto geometry = threepp::ConeGeometry::create(1, 4);
    auto material = threepp::MeshBasicMaterial::create();
    material->color = threepp::Color::blanchedalmond;

    std::shared_ptr<threepp::Mesh> spikeMesh = threepp::Mesh::create(
            geometry,
            material);

    spikeMesh->rotateX(threepp::math::PI / 2);
    spikeMesh->position = position;

    return spikeMesh;
}
