//
// Created by Jalma on 27.03.2023.
//

#ifndef THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP
#define THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP

#include "threepp/threepp.hpp"

//Be more spefici when you only need specific things

using namespace threepp;

//make namespace utils

std::shared_ptr<Mesh> createBox(BoxGeometry::Params params, float position);

std::shared_ptr<Mesh> createPlane(float x, float y);

std::shared_ptr<Mesh> createStlModel(const std::string& path);




#endif //THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP
