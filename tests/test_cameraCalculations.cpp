//
// Created by Jalma on 30/04/2023.
//
#include "player/cameraAttacher.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/MathUtils.hpp"

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("Default Constructor Test"){
    CameraAttacher cameraCalculations;

    REQUIRE_THAT(cameraCalculations.getCameraAngle(), Catch::Matchers::WithinRel(1.046, 0.1));
    REQUIRE_THAT(cameraCalculations.getDistanceFromObj(), Catch::Matchers::WithinRel(-5.0,0.01));

    REQUIRE_THAT(cameraCalculations.getPosition().x, Catch::Matchers::WithinRel(0, 0.01));
    REQUIRE_THAT(cameraCalculations.getPosition().y, Catch::Matchers::WithinRel(-5.0, 0.01));
    REQUIRE_THAT(cameraCalculations.getPosition().z, Catch::Matchers::WithinRel(5.0, 0.01));
}