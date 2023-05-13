
#include "coin/coinVisualizer.hpp"

CoinVisualizer::CoinVisualizer() {
    coin = createCoin();
    coin->position = {-10, 0, 2};
}

void CoinVisualizer::updateCoinPosition(threepp::Vector3 newPosition) const {
    coin->position = newPosition;
}

std::shared_ptr<threepp::Mesh> CoinVisualizer::createCoin() {
    auto geometry = threepp::CylinderGeometry::create(2, 2, 1);
    geometry->center();
    auto material = threepp::MeshBasicMaterial::create();
    material->color = threepp::Color::yellow;

    std::shared_ptr<threepp::Mesh> coinMesh = threepp::Mesh::create(geometry, material);

    auto innerGeometry = threepp::CylinderGeometry::create(1, 1, 1.5);
    innerGeometry->center();
    auto innerMaterial = threepp::MeshBasicMaterial::create();
    innerMaterial->color = 0xffe400;

    auto innerMesh = threepp::Mesh::create(innerGeometry, innerMaterial);

    coinMesh->add(innerMesh);

    return coinMesh;
}
