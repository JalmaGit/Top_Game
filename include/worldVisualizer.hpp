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

    WorldVisualizer(float x, float y) : mapSizeX_(x), mapSizeY_(y) {
        flor = addPlane(x, y);
    }

    void addBox(threepp::Vector3 boxPosition, threepp::Vector3 boxSize) {
        boxes.emplace_back(createBox(boxPosition, boxSize));
    }


private:
    float mapSizeX_{};
    float mapSizeY_{};
    threepp::Vector3 boxPosition_{20, 0, 2.5};
    threepp::Vector3 boxPosition1_{0, 0, 2.5};

    std::shared_ptr<threepp::Mesh> addPlane(float width, float length);

    std::shared_ptr<threepp::Mesh> createBox(threepp::Vector3 boxPosition, threepp::Vector3 boxSize);


};

#endif //TOP_GAME_WORLDCALCULATIONS_HPP
