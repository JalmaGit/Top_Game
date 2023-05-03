
#include "moveAbleObject.hpp"
#include <threepp/math/Vector3.hpp> //threepp use <> bc it's not part of my own library
#include <threepp/math/MathUtils.hpp>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>


TEST_CASE("Zero Position") {

    MoveAble moveAbleObject;
    Vector3 ZeroPosition{0, 0, 0};
    float rotation = 0;

    CHECK(moveAbleObject.position == ZeroPosition);
    CHECK(moveAbleObject.position == moveAbleObject.getPosition());
    CHECK(moveAbleObject.getRotation() == rotation);
}

TEST_CASE("Checking Default Constructor"){
    MoveAble moveAbleObject;
    Vector3 expectedPosition{0, 0, 0};

    CHECK(moveAbleObject.getRotation() == 0);
    CHECK(moveAbleObject.getPosition() == expectedPosition);
    CHECK(moveAbleObject.getTurnSpeed() == 1);
    CHECK(moveAbleObject.getBaseSpeed() == 50);
}

TEST_CASE("Forward, Backwards and Turning for small velocity and large turnDirection") {

    MoveAble moveAbleObject;
    Vector3 expectedPosition{0, 0, 0};

    float turnSpeed = math::PI / 8;
    float baseSpeed = 1;

    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;

    moveAbleObject.setTurnSpeed(math::PI / 8);
    moveAbleObject.setBaseSpeed(1);

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed * velocity * std::sin(currentAngle), baseSpeed * velocity * std::cos(currentAngle), 0};
        moveAbleObject.move(velocity, turnDirection);

        REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

        moveAbleObject.move(-velocity, 0);
        expectedPosition -= {baseSpeed * velocity * std::sin(currentAngle), baseSpeed * velocity * std::cos(currentAngle), 0};

        REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}

TEST_CASE("Forward and Backwards"){
    MoveAble moveAbleObject;
    moveAbleObject.setBaseSpeed(1);
    Vector3 expectedPosition{0, 10, 0};

    moveAbleObject.move(10,0);

    REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    expectedPosition = {0,0,0};

    moveAbleObject.resetPosAndRotation();

    REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    expectedPosition = {0,-20,0};

    moveAbleObject.move(-20,0);

    REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    CHECK(moveAbleObject.getPosition() == expectedPosition);

}

TEST_CASE("Simple Forward with a 90 degree turn"){
    MoveAble moveAbleObject;
    moveAbleObject.setBaseSpeed(1);

    float turn = math::PI/2;

    Vector3 expectedPosition{10*std::sin(turn), 10*std::cos(turn), 0};

    moveAbleObject.move(10,turn);

    REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    expectedPosition = {0,0,0};

    moveAbleObject.resetPosAndRotation();

    REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
    REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
    REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

    expectedPosition = {0,-20,0};

    moveAbleObject.move(-20,0);

    CHECK(moveAbleObject.getPosition() == expectedPosition);
}

TEST_CASE("Forward, Backwards and Turning for high velocity and small turnDirection") {

    MoveAble moveAbleObject;
    Vector3 expectedPosition{0, 0, 0};

    float turnSpeed = math::PI / 80;
    float baseSpeed = 1000;

    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;

    moveAbleObject.setTurnSpeed(math::PI / 80);
    moveAbleObject.setBaseSpeed(1000);

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed * velocity * std::sin(currentAngle), baseSpeed * velocity * std::cos(currentAngle), 0};
        moveAbleObject.move(velocity, turnDirection);

        REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));

        moveAbleObject.move(-velocity, 0);
        expectedPosition -= {baseSpeed * velocity * std::sin(currentAngle), baseSpeed * velocity * std::cos(currentAngle), 0};

        REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}

TEST_CASE("Moving in Circle") {
    MoveAble moveAbleObject;
    Vector3 expectedPosition{0, 0, 0};

    float turnSpeed = math::PI / 80;
    float baseSpeed = 1000;

    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;

    moveAbleObject.setTurnSpeed(math::PI / 80);
    moveAbleObject.setBaseSpeed(1000);

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed * velocity * std::sin(currentAngle), baseSpeed * velocity * std::cos(currentAngle), 0};
        moveAbleObject.move(velocity, turnDirection);

        REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}

TEST_CASE("Circles not from Zero Position"){
    Vector3 startPos{100, 100, 0};
    MoveAble moveAbleObject{startPos};
    Vector3 expectedPosition{100, 100, 0};

    float turnSpeed = math::PI / 80;
    float baseSpeed = 1000;

    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;

    moveAbleObject.setTurnSpeed(math::PI / 80);
    moveAbleObject.setBaseSpeed(1000);

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed * velocity * std::sin(currentAngle), baseSpeed * velocity * std::cos(currentAngle), 0};
        moveAbleObject.move(velocity, turnDirection);

        REQUIRE_THAT(moveAbleObject.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(moveAbleObject.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(moveAbleObject.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }

}