
#include "player/moveAble.hpp"
#include <threepp/math/Vector3.hpp>
#include <threepp/math/MathUtils.hpp>
#include <cmath>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>


TEST_CASE("Zero position") {

    MoveAble moveAble;
    threepp::Vector3 ZeroPosition{0, 0, 0};
    float rotation = 0;

    CHECK(moveAble.position == ZeroPosition);
    CHECK(moveAble.position == moveAble.getPosition());
    CHECK(moveAble.getRotation() == rotation);
}

TEST_CASE("Checking Constructor"){

    MoveAble moveAble;
    threepp::Vector3 expectedPosition{0, 0, 0};

    CHECK(moveAble.getRotation() == 0);
    CHECK(moveAble.getPosition() == expectedPosition);
    CHECK(moveAble.getTurnSpeed() == 1);
    CHECK(moveAble.getBaseSpeed() == 50);
}

TEST_CASE("Forward and Backwards") {

    MoveAble moveAble;
    moveAble.setBaseSpeed(10);
    moveAble.setForceVector(1, 0, 1);
    moveAble.move();

    threepp::Vector3 expectedPosition{0, 10, 0};

    REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    expectedPosition = {0,0,0};

    moveAble.resetPosAndRotation();

    REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    moveAble.setForceVector(-1, 0, 2);
    moveAble.move();

    expectedPosition = {0,-20,0};

    REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    CHECK(moveAble.getPosition() == expectedPosition);

}

TEST_CASE("Simple Forward with a 90 degree turn"){

    MoveAble moveAble;
    moveAble.setBaseSpeed(1);
    moveAble.setTurnSpeed(threepp::math::PI / 2);

    moveAble.setForceVector(1, 1, 1);
    moveAble.move();

    threepp::Vector3 expectedPosition { std::sin(threepp::math::PI/2), std::cos(threepp::math::PI/2), 0};

    REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    moveAble.resetPosAndRotation();

    REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(0.0, 0.1));
    REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(0.0, 0.1));
    REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(0.0, 0.1));
}

TEST_CASE("Forward, Backwards and Turning for small velocity and large turnDirection") {

    MoveAble moveAble;
    threepp::Vector3 expectedPosition{0, 0, 0};

    float turnSpeed = threepp::math::PI / 8;
    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;

    moveAble.setTurnSpeed(threepp::math::PI / 8);
    moveAble.setBaseSpeed(1);

    for (int i = 0; currentAngle < 2 * threepp::math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {velocity * std::sin(currentAngle),velocity * std::cos(currentAngle), 0};

        moveAble.setForceVector(1, 1, 1);
        moveAble.move();

        REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

        moveAble.setForceVector(-1, 0, 1);
        moveAble.move();
        expectedPosition -= {velocity * std::sin(currentAngle), velocity * std::cos(currentAngle), 0};

        REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}

TEST_CASE("Forward, Backwards and Turning for high velocity and small turnDirection") {

    MoveAble moveAble;
    threepp::Vector3 expectedPosition{0, 0, 0};

    float turnSpeed = threepp::math::PI / 80;
    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;
    float baseSpeed = 1000;

    moveAble.setTurnSpeed(threepp::math::PI / 80);
    moveAble.setBaseSpeed(1000);

    for (int i = 0; currentAngle < 2 * threepp::math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed*velocity * std::sin(currentAngle),baseSpeed*velocity * std::cos(currentAngle), 0};

        moveAble.setForceVector(1, 1, 1);
        moveAble.move();

        REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

        moveAble.setForceVector(-1, 0, 1);
        moveAble.move();
        expectedPosition -= {baseSpeed*velocity * std::sin(currentAngle), baseSpeed*velocity * std::cos(currentAngle), 0};

        REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}

TEST_CASE("Moving in Circle") {

    MoveAble moveAble;
    threepp::Vector3 expectedPosition{0, 0, 0};

    float turnSpeed = threepp::math::PI / 8;
    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;
    float baseSpeed = 10;

    moveAble.setTurnSpeed(threepp::math::PI / 8);
    moveAble.setBaseSpeed(10);

    for (int i = 0; currentAngle < 2 * threepp::math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed*velocity * std::sin(currentAngle),baseSpeed*velocity * std::cos(currentAngle), 0};

        moveAble.setForceVector(1, 1, 1);
        moveAble.move();

        REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}

TEST_CASE("Circles not from Zero position") {

    MoveAble moveAble{{20, 20, 0}};
    threepp::Vector3 expectedPosition{20, 20, 0};

    float turnSpeed = threepp::math::PI / 8;
    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;
    float baseSpeed = 10;

    moveAble.setTurnSpeed(threepp::math::PI / 8);
    moveAble.setBaseSpeed(10);

    for (int i = 0; currentAngle < 2 * threepp::math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed*velocity * std::sin(currentAngle),baseSpeed*velocity * std::cos(currentAngle), 0};

        moveAble.setForceVector(1, 1, 1);
        moveAble.move();

        REQUIRE_THAT(moveAble.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAble.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAble.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}