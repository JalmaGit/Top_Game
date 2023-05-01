//
// Created by Jalma on 28/03/2023.
//

#include "geometryCreation.hpp"
#include "world.hpp"

Box3 WorldGen::createUpperWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params topBoxParams{params.width, params.height, 100};

    auto upperBox = utils::createBox(topBoxParams,0);
    upperBox->position.y = params.depth / 2 + topBoxParams.depth / 2;
    Box3 upperHitBox;

    return upperHitBox.setFromObject(*upperBox);
}

Box3 WorldGen::createLowerWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params downBoxParams{params.width, params.height, 100};

    auto lowerBox = utils::createBox(downBoxParams,0);
    lowerBox->position.y = -params.depth / 2 - downBoxParams.depth / 2;
    Box3 lowerHitBox;

    return lowerHitBox.setFromObject(*lowerBox);
}

Box3 WorldGen::createRightWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params rightBoxParams{100, params.height, params.depth};
    auto rightBox = utils::createBox(rightBoxParams,0);
    rightBox->position.x = params.width / 2 + rightBoxParams.width / 2;
    Box3 rightHitBox;

    return rightHitBox.setFromObject(*rightBox);
}

Box3 WorldGen::createLeftWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params leftBoxParams{100, params.height, params.depth};

    auto leftBox = utils::createBox(leftBoxParams,0);
    leftBox->position.x = -params.width / 2 - leftBoxParams.width / 2;
    Box3 leftHitBox;

    return leftHitBox.setFromObject(*leftBox);
}