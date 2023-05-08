//
// Created by Jalma on 08/05/2023.
//

#ifndef TOP_GAME_SPIKEVISUALIZER_HPP
#define TOP_GAME_SPIKEVISUALIZER_HPP

#include <threepp/math/Vector3.hpp>
#include <threepp/objects/Mesh.hpp>
#include <threepp/geometries/CylinderGeometry.hpp>
#include <threepp/materials/MeshBasicMaterial.hpp>

class SpikeVisualizer{
public:
    std::shared_ptr<threepp::Mesh> coin;

    explicit SpikeVisualizer(threepp::Vector3 newPosition){

        coin->position = newPosition;
    }

    void createCoin(){

    }

private:

};

#endif //TOP_GAME_SPIKEVISUALIZER_HPP
