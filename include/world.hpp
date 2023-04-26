//
// Created by Jalma on 27.03.2023.
//

#ifndef THREEPP_VCPKG_TEST_WORLD_HPP
#define THREEPP_VCPKG_TEST_WORLD_HPP

#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"
#include "iostream"

class WorldGen {
public:
    std::shared_ptr<Mesh> worldFlor;
    std::shared_ptr<Mesh> boxInWorld;
    std::vector<Box3> worldHitBoxes;

    WorldGen(float x, float y):mapSizeX_(x),mapSizeY_(y){
        worldFlor = utils::createPlane(x,y);
        boxInWorld = utils::createBox(boxParams_, boxPos_);

        worldHitBoxes.emplace_back(createUpperWorldEdge(edgeBox_));
        worldHitBoxes.emplace_back(createLowerWorldEdge(edgeBox_));
        worldHitBoxes.emplace_back(createRightWorldEdge(edgeBox_));
        worldHitBoxes.emplace_back(createLeftWorldEdge(edgeBox_));
        addHitBox();
    }


private:
    float boxSize_{25};
    float boxPos_{50};
    float mapSizeX_{};
    float mapSizeY_{};

    Box3 box3_;
    BoxGeometry::Params edgeBox_{mapSizeX_, 30, mapSizeY_};
    BoxGeometry::Params boxParams_{boxSize_, boxSize_, boxSize_};

    //Made worldHitBoxes better / ask if it is better

    void addHitBox(){
        worldHitBoxes.emplace_back(box3_.setFromObject(*boxInWorld));
    }

    static Box3 createUpperWorldEdge(BoxGeometry::Params params_);

    static Box3 createLowerWorldEdge(BoxGeometry::Params params_);

    static Box3 createRightWorldEdge(BoxGeometry::Params params_);

    static Box3 createLeftWorldEdge(BoxGeometry::Params params_);

};


#endif //THREEPP_VCPKG_TEST_WORLD_HPP
