//
// Created by Jalma on 27.03.2023.
//

#ifndef THREEPP_VCPKG_TEST_WORLD_HPP
#define THREEPP_VCPKG_TEST_WORLD_HPP

#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"
#include "iostream"

class WorldGen : GeometryCreation{ //Spør Lærer om dette er en lur ide
public:
    float mapSizeX{};
    float mapSizeY{};
    std::shared_ptr<Mesh> worldFlor;
    std::shared_ptr<Mesh> boxInWorld;
    std::vector<Box3> worldHitBoxes;
    Box3 box3;

    WorldGen(float x, float y):mapSizeX(x),mapSizeY(y){
        worldFlor = createPlane(x,y);
        boxInWorld = createBox(boxParams, boxPos);
        getHitboxes(worldHitBoxes);
    }


private:
    float boxSize{25};
    float boxPos{50};

    BoxGeometry::Params boxParams{boxSize, boxSize, boxSize};

    void getHitboxes(std::vector<Box3>& hitBoxes){
        getWorldEdge(hitBoxes);
        addHitBox(hitBoxes);
    }

    void getWorldEdge(std::vector<Box3>& edgeHitBox) {
        BoxGeometry::Params edgeBox{mapSizeX, 30, mapSizeY};
        edgeHitBox.emplace_back(createUpperWorldEdge(edgeBox));
        edgeHitBox.emplace_back(createLowerWorldEdge(edgeBox));
        edgeHitBox.emplace_back(createRightWorldEdge(edgeBox));
        edgeHitBox.emplace_back(createLeftWorldEdge(edgeBox));
    }

    void addHitBox(std::vector<Box3>& hitbox){
        hitbox.emplace_back(box3.setFromObject(*boxInWorld));
    }

    Box3 createUpperWorldEdge(BoxGeometry::Params params);

    Box3 createLowerWorldEdge(BoxGeometry::Params params);

    Box3 createRightWorldEdge(BoxGeometry::Params params);

    Box3 createLeftWorldEdge(BoxGeometry::Params params);

    PlaneGeometry::Params mapSize{mapSizeX, mapSizeY};
    //Not in use yet, more development needed

};


#endif //THREEPP_VCPKG_TEST_WORLD_HPP
