//
// Created by Jalma on 30/04/2023.
//

#ifndef TOP_GAME_WORLDCALCULATIONS_HPP
#define TOP_GAME_WORLDCALCULATIONS_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/objects/Group.hpp"
#include <iostream>

class WorldVisualizer {
public:

    std::shared_ptr<threepp::Mesh> flor;
    std::vector<std::shared_ptr<threepp::Mesh>> boxes;

    WorldVisualizer(float mapSizeX, float mapSizeY) {
        flor = createPlane(mapSizeX, mapSizeY);
    }

    void addBox(threepp::Vector3 boxPosition, threepp::Vector3 boxSize) {
        boxes.emplace_back(createBox(boxPosition, boxSize));
    }

private:

    std::shared_ptr<threepp::Mesh> createPlane(float width, float length);

    std::shared_ptr<threepp::Mesh> createBox(threepp::Vector3 boxPosition, threepp::Vector3 boxSize);

};

#endif //TOP_GAME_WORLDCALCULATIONS_HPP
