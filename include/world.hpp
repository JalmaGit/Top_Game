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

    WorldGen(float x, float y):mapSizeX(x),mapSizeY(y){
        worldFlor = utils::createPlane(x,y);
        boxInWorld = utils::createBox(boxParams, boxPos);

        worldHitBoxes.emplace_back(createUpperWorldEdge(edgeBox));
        worldHitBoxes.emplace_back(createLowerWorldEdge(edgeBox));
        worldHitBoxes.emplace_back(createRightWorldEdge(edgeBox));
        worldHitBoxes.emplace_back(createLeftWorldEdge(edgeBox));
        addHitBox();
    }


private:
    float boxSize{25};
    float boxPos{50};
    float mapSizeX{};
    float mapSizeY{};

    Box3 box3;
    BoxGeometry::Params edgeBox{mapSizeX, 30, mapSizeY};
    BoxGeometry::Params boxParams{boxSize, boxSize, boxSize};

    //Made worldHitBoxes better / ask if it is better

    void addHitBox(){
        worldHitBoxes.emplace_back(box3.setFromObject(*boxInWorld));
    }

    static Box3 createUpperWorldEdge(BoxGeometry::Params params);

    static Box3 createLowerWorldEdge(BoxGeometry::Params params);

    static Box3 createRightWorldEdge(BoxGeometry::Params params);

    static Box3 createLeftWorldEdge(BoxGeometry::Params params);

};


#endif //THREEPP_VCPKG_TEST_WORLD_HPP
