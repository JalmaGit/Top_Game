
#include "Deperecated/geometryCreationOld.hpp"
#include "Deperecated/worldOld.hpp"

threepp::Box3 WorldGen::createUpperWorldEdge(const threepp::BoxGeometry::Params params) {
    threepp::BoxGeometry::Params topBoxParams{params.width, params.height, 100};

    auto upperBox = utils::createBox(topBoxParams, 0);
    upperBox->position.y = params.depth / 2 + topBoxParams.depth / 2;
    Box3 upperHitBox;

    return upperHitBox.setFromObject(*upperBox);
}

threepp::Box3 WorldGen::createLowerWorldEdge(const BoxGeometry::Params params) {
    threepp::BoxGeometry::Params downBoxParams{params.width, params.height, 100};

    auto lowerBox = utils::createBox(downBoxParams, 0);
    lowerBox->position.y = -params.depth / 2 - downBoxParams.depth / 2;
    threepp::Box3 lowerHitBox;

    return lowerHitBox.setFromObject(*lowerBox);
}

threepp::Box3 WorldGen::createRightWorldEdge(const threepp::BoxGeometry::Params params) {
    BoxGeometry::Params rightBoxParams{100, params.height, params.depth};

    auto rightBox = utils::createBox(rightBoxParams, 0);
    rightBox->position.x = params.width / 2 + rightBoxParams.width / 2;
    threepp::Box3 rightHitBox;

    return rightHitBox.setFromObject(*rightBox);
}

threepp::Box3 WorldGen::createLeftWorldEdge(const threepp::BoxGeometry::Params params) {
    threepp::BoxGeometry::Params leftBoxParams{100, params.height, params.depth};

    auto leftBox = utils::createBox(leftBoxParams, 0);
    leftBox->position.x = -params.width / 2 - leftBoxParams.width / 2;
    threepp::Box3 leftHitBox;

    return leftHitBox.setFromObject(*leftBox);
}

WorldGen::WorldGen(float width, float height) : mapSizeX_(width), mapSizeY_(height) {
    worldFlor = utils::createPlane(width, height);
    boxInWorld = utils::createBox(boxParams_, boxPos_);

    worldHitBoxes.emplace_back(createUpperWorldEdge(edgeBox_));
    worldHitBoxes.emplace_back(createLowerWorldEdge(edgeBox_));
    worldHitBoxes.emplace_back(createRightWorldEdge(edgeBox_));
    worldHitBoxes.emplace_back(createLeftWorldEdge(edgeBox_));

    addHitBox();
}
