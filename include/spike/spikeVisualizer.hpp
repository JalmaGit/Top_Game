#ifndef TOP_GAME_SPIKEVISUALIZER_HPP
#define TOP_GAME_SPIKEVISUALIZER_HPP

#include <threepp/math/Vector3.hpp>
#include <threepp/math/MathUtils.hpp>
#include <threepp/objects/Mesh.hpp>
#include <threepp/geometries/ConeGeometry.hpp>
#include <threepp/materials/MeshBasicMaterial.hpp>

class SpikeVisualizer {
public:
    std::vector<std::shared_ptr<threepp::Mesh>> spikes;

    static std::shared_ptr<threepp::Mesh> createSpike(threepp::Vector3 &position);
};

#endif //TOP_GAME_SPIKEVISUALIZER_HPP
