
#include "playerHandler.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/MathUtils.hpp"

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("Zero Position") {

    Player player;
    Vector3 ZeroPosition{0, 0, 0};
    float rotation = 0;

    CHECK(player.position == ZeroPosition);
    CHECK(player.position == player.getPosition());
    CHECK(player.getRotation() == rotation);
}

TEST_CASE("Forward, Backwards and Turning") {

    Player player;
    Vector3 expectedPosition{0, 0, 0};

    float velocity = 1;
    float turnSpeed = math::PI / 8;
    float currentAngle = 0;

    for (int i = 0; currentAngle < 2 * math::PI; i++) {

        currentAngle += turnSpeed;
        expectedPosition += {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};
        player.move(velocity, turnSpeed);

        CHECK(player.getPosition() == expectedPosition);

        player.move(-velocity, 0);
        expectedPosition -= {velocity * cos(currentAngle), velocity * sin(currentAngle), 0};

        CHECK(player.getPosition() == expectedPosition);
    }

}

TEST_CASE("Checking Default Constructor"){
    Player player;
    Vector3 expectedPosition{0, 0, 0};

    CHECK(player.getPosition() == expectedPosition);
    CHECK(player.getTurnSpeed() == 1);
    CHECK(player.getBaseSpeed() == 50);
    CHECK(player.getHealth() == 100);
    CHECK(player.getScore() == 0);
}

TEST_CASE("Functions"){
    Player player;

    player.setTurnSpeed(100);
    player.setBaseSpeed(5000);
    player.setHealth(200);
    player.setScore(1000);

    CHECK(player.getTurnSpeed() == 100);
    CHECK(player.getBaseSpeed() == 5000);
    CHECK(player.getHealth() == 200);
    CHECK(player.getScore() == 1000);

    player.addScore(20);

    CHECK(player.getScore() == 1020);

    player.removeScore(40);

    CHECK(player.getScore() == 980);
}
