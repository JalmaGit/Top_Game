//
// Created by Jalma on 27.03.2023.
//

#ifndef THREEPP_VCPKG_TEST_WORLD_HPP
#define THREEPP_VCPKG_TEST_WORLD_HPP

#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"

class worldGen {
public:
    float mapSizeX{};
    float mapSizeY{};
    std::string path {""};

  //  PlaneGeometry::Params pictureSize{mapSizeX,mapSizeY};
    auto getWorldFlor(){
        return createPlane(mapSize);
    }

    auto getWorldEdge();

private:
    PlaneGeometry::Params mapSize{mapSizeX,mapSizeY};

    auto setWorldEdge(){

    }

};


#endif //THREEPP_VCPKG_TEST_WORLD_HPP
