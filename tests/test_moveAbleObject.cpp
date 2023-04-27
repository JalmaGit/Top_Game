
#include "moveAbleObject.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"
#include <iostream>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>



TEST_CASE("Zero Position") {

    MoveAbleObject moveAbleObject;
    Vector3 ZeroPosition{0,0,0};

    CHECK(moveAbleObject.position == ZeroPosition);
    CHECK(moveAbleObject.position == moveAbleObject.getPosition());

    Vector3 changedPosition{1,0,0};
    Vector3 move{1,0,0};
    moveAbleObject.move(move);



    CHECK(moveAbleObject.getPosition() == changedPosition);

    Vector3 move1{2,0,0};
    Vector3 changedPosition1{1,2,0};
    moveAbleObject.setRotation(math::PI/2);
    moveAbleObject.move(move1);

    std::cout << moveAbleObject.getPosition().y << std::endl;
    std::cout << changedPosition1.y << std::endl;

    CHECK(moveAbleObject.getPosition().y == changedPosition1.y);
    CHECK(moveAbleObject.getPosition().x == changedPosition1.x);



}