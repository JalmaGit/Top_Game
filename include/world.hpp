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
    std::shared_ptr<Mesh> boxInWorld;
    std::array<Box3,4> worldWallHitBox;

    WorldGen(float x, float y):mapSizeX(x),mapSizeY(y){
        worldFlor = createPlane(x,y);
        getWorldEdge(worldWallHitBox);
    }

    [[nodiscard]] auto getBox() const{
        BoxGeometry::Params boxParams{boxSize, boxSize, boxSize};
        auto box = createBox(boxParams,boxPos);
        return box;
    }

private:
    float boxSize{25};
    float boxPos{50};

    void getWorldEdge(std::array<Box3,4>& edgeHitBox) {
        BoxGeometry::Params edgeBox{mapSizeX, 30, mapSizeY};
        edgeHitBox[0] = createUpperWorldEdge(edgeBox);
        edgeHitBox[1] = createLowerWorldEdge(edgeBox);
        edgeHitBox[2] = createRightWorldEdge(edgeBox);
        edgeHitBox[3] = createLeftWorldEdge(edgeBox);
    }

    Box3 createUpperWorldEdge(BoxGeometry::Params params);

    Box3 createLowerWorldEdge(BoxGeometry::Params params);

    Box3 createRightWorldEdge(BoxGeometry::Params params);

    Box3 createLeftWorldEdge(BoxGeometry::Params params);

    PlaneGeometry::Params mapSize{mapSizeX, mapSizeY};
    //Not in use yet, more development needed

};


#endif //THREEPP_VCPKG_TEST_WORLD_HPP
