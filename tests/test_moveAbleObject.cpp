
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("my_test_case", "[my_tag]") {
    REQUIRE(1 + 1 == 2);
}