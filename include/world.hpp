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
    float mapSizeX{};
    float mapSizeY{};
    std::shared_ptr<Mesh> worldFlor;

    WorldGen(float x, float y):mapSizeX(x),mapSizeY(y){
        worldFlor = createPlane(x,y);
    }



    void getWorldEdge(Box3 worldHitBox[4]) {
        BoxGeometry::Params edgeBox{mapSizeX, 30, mapSizeY};
        worldHitBox[0] = createUpperWorldEdge(edgeBox);
        worldHitBox[1] = createLowerWorldEdge(edgeBox);
        worldHitBox[2] = createRightWorldEdge(edgeBox),
                worldHitBox[3] = createLeftWorldEdge(edgeBox);
    }

private:
    Box3 createUpperWorldEdge(BoxGeometry::Params params);

    Box3 createLowerWorldEdge(BoxGeometry::Params params);

    Box3 createRightWorldEdge(BoxGeometry::Params params);

    Box3 createLeftWorldEdge(BoxGeometry::Params params);

    PlaneGeometry::Params mapSize{mapSizeX, mapSizeY};
    //Not in use yet, more development needed

};


#endif //THREEPP_VCPKG_TEST_WORLD_HPP
