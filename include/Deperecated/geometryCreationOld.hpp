#ifndef TOP_GAME_GEOMETRY_CREATION_HPP
#define TOP_GAME_GEOMETRY_CREATION_HPP

#include <threepp/threepp.hpp>

using namespace threepp;

namespace utils {

    std::shared_ptr<Mesh> createBox(BoxGeometry::Params params, float position);

    std::shared_ptr<Mesh> createPlane(float x, float y);

    std::shared_ptr<Mesh> createStlModel(const std::string &path);
}

#endif //Top_Game_GEOMETRY_CREATION_HPP
