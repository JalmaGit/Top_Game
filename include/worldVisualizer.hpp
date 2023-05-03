//
// Created by Jalma on 30/04/2023.
//

#ifndef TOP_GAME_WORLDCALCULATIONS_HPP
#define TOP_GAME_WORLDCALCULATIONS_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/objects/Group.hpp"
#include <iostream>

using namespace threepp;

class WorldVisualizer {
public:

    std::shared_ptr<Mesh> flor;
    std::vector<std::shared_ptr<Mesh>> boxes;

    WorldVisualizer(float x, float y):mapSizeX_(x),mapSizeY_(y){
        flor = addPlane(x,y);
    }

    void addBox(Vector3 boxPosition, Vector3 boxSize){
        boxes.emplace_back(createBox(boxPosition, boxSize));
    }


private:
    float mapSizeX_{};
    float mapSizeY_{};
    Vector3 boxPosition_{20,0,2.5};
    Vector3 boxPosition1_{0,0,2.5};

    std::shared_ptr<Mesh> addPlane(float width, float length);

    std::shared_ptr<Mesh> createBox(Vector3 boxPosition, Vector3 boxSize);


};

#endif //TOP_GAME_WORLDCALCULATIONS_HPP
