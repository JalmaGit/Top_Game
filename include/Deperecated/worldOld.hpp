#ifndef TOP_GAME_WORLD_HPP
#define TOP_GAME_WORLD_HPP

#include <threepp/threepp.hpp>
#include "geometryCreationOld.hpp"
#include "iostream"

class WorldGen {
public:
    std::shared_ptr<Mesh> worldFlor;
    std::shared_ptr<Mesh> boxInWorld;
    std::vector<Box3> worldHitBoxes;

    WorldGen(float width, float height);


private:
    float boxSize_{25};
    float boxPos_{50};
    float mapSizeX_{};
    float mapSizeY_{};

    Box3 box3_;
    BoxGeometry::Params edgeBox_{mapSizeX_, 30, mapSizeY_};
    BoxGeometry::Params boxParams_{boxSize_, boxSize_, boxSize_};

    //Made worldHitBoxes better / ask if it is better

    void addHitBox() {
        worldHitBoxes.emplace_back(box3_.setFromObject(*boxInWorld));
    }

    static Box3 createUpperWorldEdge(BoxGeometry::Params params_);

    static Box3 createLowerWorldEdge(BoxGeometry::Params params_);

    static Box3 createRightWorldEdge(BoxGeometry::Params params_);

    static Box3 createLeftWorldEdge(BoxGeometry::Params params_);

};


#endif //THREEPP_VCPKG_TEST_WORLD_HPP
