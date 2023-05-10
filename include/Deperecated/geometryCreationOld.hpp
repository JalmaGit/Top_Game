#ifndef THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP
#define THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP

#include <threepp/threepp.hpp>

using namespace threepp;

namespace utils {

    std::shared_ptr<Mesh> createBox(BoxGeometry::Params params, float position);

    std::shared_ptr<Mesh> createPlane(float x, float y);

    std::shared_ptr<Mesh> createStlModel(const std::string &path);

}


#endif //Top_Game_GEOMETRY_CREATION_HPP
