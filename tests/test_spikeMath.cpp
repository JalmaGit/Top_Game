#include "spike/spikeMath.hpp"

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("Checking Constructor"){

    SpikeMath spikeMath;

    CHECK(spikeMath.dealDamage() == 50);
}

TEST_CASE("Function Tests"){

    SpikeMath spikeMath;

    spikeMath.setNewDamage(10);

    CHECK(spikeMath.dealDamage() == 10);
}