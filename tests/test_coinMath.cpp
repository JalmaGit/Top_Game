#include <threepp/math/Vector3.hpp>
#include <vector>
#include "coin/coinMath.hpp"

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>


TEST_CASE("Default Constructor Test"){
   CoinMath coinMath;

   CHECK(coinMath.givePoints() == 100);
}

TEST_CASE("Functions"){
    CoinMath coinMath;

    std::vector<threepp::Vector3> testPositionVector;
    threepp::Vector3 testPosition{0,0,0};
    testPositionVector.emplace_back(testPosition);
    testPositionVector.emplace_back(testPosition);

    coinMath.setPossiblePositions(testPositionVector);

    REQUIRE_THAT(coinMath.getNewPosition().x, Catch::Matchers::WithinRel(0, 0.001));
    REQUIRE_THAT(coinMath.getNewPosition().y, Catch::Matchers::WithinRel(0, 0.001));
    REQUIRE_THAT(coinMath.getNewPosition().z, Catch::Matchers::WithinRel(0, 0.001));

}