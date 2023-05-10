//
// Created by Jalma on 08/05/2023.
//

#ifndef TOP_GAME_SPIKEVISUALIZER_HPP
#define TOP_GAME_SPIKEVISUALIZER_HPP

#include "threepp/math/Vector3.hpp"
#include "threepp/math/MathUtils.hpp"
#include "threepp/objects/Mesh.hpp"
#include "threepp/geometries/ConeGeometry.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"

class SpikeVisualizer {
public:
    std::vector<std::shared_ptr<threepp::Mesh>> spike;

    explicit SpikeVisualizer(const std::vector<threepp::Vector3> &positions) {
        for (auto &element: positions) {
            spike.emplace_back(createSpike(element));
        }
    }

    static std::shared_ptr<threepp::Mesh> createSpike(threepp::Vector3 position) {
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

private:

};

#endif //TOP_GAME_SPIKEVISUALIZER_HPP
