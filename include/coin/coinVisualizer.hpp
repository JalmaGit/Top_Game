#ifndef TOP_GAME_COINVISUALIZER_HPP
#define TOP_GAME_COINVISUALIZER_HPP

#include <threepp/math/Vector3.hpp>
#include <threepp/objects/Mesh.hpp>
#include <threepp/geometries/CylinderGeometry.hpp>
#include <threepp/materials/MeshBasicMaterial.hpp>

class CoinVisualizer {
public:
    std::shared_ptr<threepp::Mesh> coin;

    explicit CoinVisualizer();

    void updateCoinPosition(threepp::Vector3 newPosition) const;

    static std::shared_ptr<threepp::Mesh> createCoin();
};

#endif //TOP_GAME_COINVISUALIZER_HPP
