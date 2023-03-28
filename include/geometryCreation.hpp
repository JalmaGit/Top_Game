//
// Created by Jalma on 27.03.2023.
//

#ifndef THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP
#define THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

std::shared_ptr<Mesh> createBox(BoxGeometry::Params params);

std::shared_ptr<Mesh> createPlane(const PlaneGeometry::Params &params);

std::shared_ptr<Mesh> createStlModel();

#endif //THREEPP_VCPKG_TEST_GEOMETRY_CREATION_HPP
