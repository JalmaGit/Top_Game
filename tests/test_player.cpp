
#include "player/player.hpp"
#include <threepp/math/Vector3.hpp>
#include <threepp/math/MathUtils.hpp>
#include <cmath>

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>


TEST_CASE("Zero position") {
    Player player;
    threepp::Vector3 ZeroPosition{0, 0, 2};
    float rotation = 0;

    CHECK(player.position == ZeroPosition);
    CHECK(player.position == player.getPosition());
    CHECK(player.getRotation() == rotation);
}

TEST_CASE("Moving in circles") {
    Player player;
    threepp::Vector3 expectedPosition{0, 0, 2};

    float turnSpeed = threepp::math::PI / 8;
    float velocity = 1;
    float turnDirection = 1;
    float currentAngle = 0;
    float baseSpeed = 10;

    player.setTurnSpeed(threepp::math::PI / 8);
    player.setBaseSpeed(10);

    for (int i = 0; currentAngle < 2 * threepp::math::PI; i++) {

        currentAngle += turnSpeed * turnDirection;
        expectedPosition += {baseSpeed*velocity * std::sin(currentAngle),
                             baseSpeed*velocity * std::cos(currentAngle),
                             0};

        player.setForceVector(1, 1, 1);
        player.move();

        REQUIRE_THAT(player.getPosition().y, Catch::Matchers::WithinRel(expectedPosition.y));
        REQUIRE_THAT(player.getPosition().x, Catch::Matchers::WithinRel(expectedPosition.x));
        REQUIRE_THAT(player.getPosition().z, Catch::Matchers::WithinRel(expectedPosition.z));
    }
}

TEST_CASE("Checking Default Constructor") {
    Player player;
    threepp::Vector3 expectedPosition{0, 0, 2};

    CHECK(player.getPosition() == expectedPosition);
    CHECK(player.getTurnSpeed() == 1);
    CHECK(player.getBaseSpeed() == 50);
    CHECK(player.getHealth() == 1000);
    CHECK(player.getScore() == 0);
}

TEST_CASE("Functions") {
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
