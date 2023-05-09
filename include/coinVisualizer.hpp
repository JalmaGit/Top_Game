//
// Created by Jalma on 08/05/2023.
//

#ifndef TOP_GAME_COINVISUALIZER_HPP
#define TOP_GAME_COINVISUALIZER_HPP

#include <threepp/math/Vector3.hpp>
#include "threepp/objects/Mesh.hpp"
#include <threepp/geometries/CylinderGeometry.hpp>
#include <threepp/materials/MeshBasicMaterial.hpp>

class CoinVisualizer{
public:
    std::shared_ptr<threepp::Mesh> coin;

    explicit CoinVisualizer(threepp::Vector3 newPosition){
        coin = createCoin();
        coin->position = newPosition;
    }

    std::shared_ptr<threepp::Mesh> createCoin(){
        auto geometry = threepp::CylinderGeometry::create(2,2,1);
        geometry->center();
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::yellow;

        std::shared_ptr<threepp::Mesh> coinMesh = threepp::Mesh::create(geometry,material);

        auto innerGeometry = threepp::CylinderGeometry::create(1,1,2);
        innerGeometry->center();
        auto innerMaterial = threepp::MeshBasicMaterial::create();
        innerMaterial->color = threepp::Color::yellow;

        auto innerMesh = threepp::Mesh::create(innerGeometry,innerMaterial);

        coinMesh->add(innerMesh);

        return coinMesh;
    }

private:

};



#endif //TOP_GAME_COINVISUALIZER_HPP
