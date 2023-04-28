
#include "moveAbleObject.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/MathUtils.hpp"

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>


TEST_CASE("Zero Position") {

    MoveAbleObject moveAbleObject;
    Vector3 ZeroPosition{0, 0, 0};
    float rotation = 0;

    CHECK(moveAbleObject.position == ZeroPosition);
    CHECK(moveAbleObject.position == moveAbleObject.getPosition());
    CHECK(moveAbleObject.getRotation() == rotation);
}

TEST_CASE("Forward, Backwards and Turning") {

    MoveAbleObject moveAbleObject;
    Vector3 expectedPosition{0, 0, 0};

    float velocity = 1;
    float turnSpeed = math::PI / 8;
    float currentAngle = 0;

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed;
        expectedPosition += {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};
        moveAbleObject.move(velocity, turnSpeed);

        CHECK(moveAbleObject.getPosition() == expectedPosition);

        moveAbleObject.move(-velocity, 0);
        expectedPosition -= {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};

        CHECK(moveAbleObject.getPosition() == expectedPosition);
    }

    moveAbleObject.setRotation(0);

    velocity = 1000;
    currentAngle = 0;
    turnSpeed = math::PI / 80;

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed;
        expectedPosition += {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};
        moveAbleObject.move(velocity, turnSpeed);

        CHECK(moveAbleObject.getPosition() == expectedPosition);


        moveAbleObject.move(-velocity, 0);
        expectedPosition -= {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};

        CHECK(moveAbleObject.getPosition() == expectedPosition);
    }

}

TEST_CASE("Moving in Circle") {

    MoveAbleObject moveAbleObject;
    Vector3 expectedPosition{0, 0, 0};

    float velocity = 1;
    float turnSpeed = math::PI / 8;
    float currentAngle = 0;

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed;
        expectedPosition += {cos(currentAngle), sin(currentAngle), 0};
        moveAbleObject.move(velocity, turnSpeed);

        CHECK(moveAbleObject.getPosition() == expectedPosition);

    }
    moveAbleObject.setRotation(0);

    velocity = 1000;
    currentAngle = 0;
    turnSpeed = math::PI / 80;

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed;
        expectedPosition += {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};
        moveAbleObject.move(velocity, turnSpeed);

        CHECK(moveAbleObject.getPosition() == expectedPosition);
    }

}

TEST_CASE("Circles not from Zero Position"){
    MoveAbleObject moveAbleObject{1,1,1};
    Vector3 expectedPosition{1, 1, 1};

    float velocity = 1;
    float turnSpeed = math::PI / 8;
    float currentAngle = 0;

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed;
        expectedPosition += {cos(currentAngle), sin(currentAngle), 0};
        moveAbleObject.move(velocity, turnSpeed);

        CHECK(moveAbleObject.getPosition() == expectedPosition);

    }
    expectedPosition = {100, 100, 100};
    moveAbleObject.setPosition(expectedPosition);
    moveAbleObject.setRotation(0);


    velocity = 1000;
    currentAngle = 0;
    turnSpeed = math::PI / 80;

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed;
        expectedPosition += {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};
        moveAbleObject.move(velocity, turnSpeed);

        CHECK(moveAbleObject.getPosition() == expectedPosition);
    }
}