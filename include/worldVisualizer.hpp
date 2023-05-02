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

    WorldVisualizer(float x, float y, const std::vector<Vector3>& boxPositions = {}):mapSizeX_(x),mapSizeY_(y){
        flor = addPlane(x,y);

        if(!boxPositions.empty()){
            std::cout << "Boxes available, generating map" << std::endl;
            for (auto element : boxPositions){
                boxes.emplace_back(createBox(element));
            }
        } else{ std::cout << "No Boxes available, empty map" << std::endl;}
    }

    void addBox(Vector3 boxPosition){
       // boxes->add(createBox(boxPosition));
    }


private:
    float mapSizeX_{};
    float mapSizeY_{};
    Vector3 boxPosition_{20,0,2.5};
    Vector3 boxPosition1_{0,0,2.5};

    std::shared_ptr<Mesh> addPlane(float width, float length);

    std::shared_ptr<Mesh> createBox(Vector3 boxPosition);


};

#endif //TOP_GAME_WORLDCALCULATIONS_HPP
