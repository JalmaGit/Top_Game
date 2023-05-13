//
// Created by Jalma on 30/04/2023.
//
#include "player/cameraAttacher.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/MathUtils.hpp"

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>


TEST_CASE("Constructor Test") {
    CameraAttacher cameraAttacher;

    REQUIRE_THAT(cameraAttacher.getCameraAngle(), Catch::Matchers::WithinRel(1.046, 0.1));
    REQUIRE_THAT(cameraAttacher.getDistanceFromObj(), Catch::Matchers::WithinRel(-5.0, 0.01));

    REQUIRE_THAT(cameraAttacher.getPosition().x, Catch::Matchers::WithinRel(0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().y, Catch::Matchers::WithinRel(-5.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().z, Catch::Matchers::WithinRel(5.0, 0.01));
}

TEST_CASE("Simple Movement") {
    CameraAttacher cameraAttacher;

    threepp::Vector3 objectToAttachPosition{0, 0, 0};
    cameraAttacher.updateTrailingCamera(objectToAttachPosition,0);

    REQUIRE_THAT(cameraAttacher.getPosition().x, Catch::Matchers::WithinRel(0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().y, Catch::Matchers::WithinRel(-5.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().z, Catch::Matchers::WithinRel(5.0, 0.01));

    objectToAttachPosition = {5,0,0};
    cameraAttacher.updateTrailingCamera(objectToAttachPosition,0);

    REQUIRE_THAT(cameraAttacher.getPosition().x, Catch::Matchers::WithinRel(5.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().y, Catch::Matchers::WithinRel(-5.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().z, Catch::Matchers::WithinRel(5.0, 0.01));

    objectToAttachPosition = {5,0,0};
    cameraAttacher.updateTrailingCamera(objectToAttachPosition,threepp::math::PI);

    REQUIRE_THAT(cameraAttacher.getPosition().x, Catch::Matchers::WithinRel(5.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().y, Catch::Matchers::WithinRel(5.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().z, Catch::Matchers::WithinRel(5.0, 0.01));

    objectToAttachPosition = {10,0,0};
    cameraAttacher.setDistanceFromObj(10);
    cameraAttacher.updateTrailingCamera(objectToAttachPosition,threepp::math::PI);

    REQUIRE_THAT(cameraAttacher.getPosition().x, Catch::Matchers::WithinRel(10.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().y, Catch::Matchers::WithinRel(10.0, 0.01));
    REQUIRE_THAT(cameraAttacher.getPosition().z, Catch::Matchers::WithinRel(5.0, 0.01));
}
