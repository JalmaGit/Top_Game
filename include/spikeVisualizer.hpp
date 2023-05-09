//
// Created by Jalma on 08/05/2023.
//

#ifndef TOP_GAME_SPIKEVISUALIZER_HPP
#define TOP_GAME_SPIKEVISUALIZER_HPP

#include <threepp/math/Vector3.hpp>
#include <threepp/math/MathUtils.hpp>
#include <threepp/objects/Mesh.hpp>
#include <threepp/geometries/ConeGeometry.hpp>
#include <threepp/materials/MeshBasicMaterial.hpp>

class SpikeVisualizer{
public:
    std::shared_ptr<threepp::Mesh> spike;

    explicit SpikeVisualizer(threepp::Vector3 newPosition){
        spike = createSpike();
        spike->position = newPosition;
    }

    std::shared_ptr<threepp::Mesh> createSpike(){
        auto geometry = threepp::ConeGeometry::create(1,3);
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::gray;

        std::shared_ptr<threepp::Mesh> spikeMesh = threepp::Mesh::create(geometry,material);
        spikeMesh->rotateX(threepp::math::PI/2);

        return spikeMesh;
    }

private:

};

#endif //TOP_GAME_SPIKEVISUALIZER_HPP
