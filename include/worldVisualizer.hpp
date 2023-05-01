//
// Created by Jalma on 30/04/2023.
//

#ifndef TOP_GAME_WORLDCALCULATIONS_HPP
#define TOP_GAME_WORLDCALCULATIONS_HPP

#include "threepp/objects/Mesh.hpp"
#include "threepp/objects/Group.hpp"

using namespace threepp;

class WorldVisualizer {
public:

    std::shared_ptr<Mesh> flor;
    std::shared_ptr<Mesh> boxes;
    std::shared_ptr<Group> boxGroup;

    WorldVisualizer(float x, float y, const std::vector<Vector3>& boxPositions):mapSizeX_(x),mapSizeY_(y){
        flor = addPlane(x,y);
        boxGroup = Group::create();
        boxes = createBox(boxPosition_);
        boxGroup->add(boxes);
        boxGroup->add(createBox(boxPosition1_));

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
