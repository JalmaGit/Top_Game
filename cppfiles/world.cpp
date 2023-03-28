//
// Created by Jalma on 28/03/2023.
//

#include "geometryCreation.hpp"

auto createUpperWorldEdge1(const BoxGeometry::Params params) {
    BoxGeometry::Params topBoxParams{params.width, params.height, 100};
    auto upperBox = createBox(topBoxParams);
    upperBox->position.y = params.depth / 2 + topBoxParams.depth / 2;
    Box3 upperHitBox;
    return upperHitBox.setFromObject(*upperBox);
}

auto createLowerWorldEdge1(const BoxGeometry::Params params) {
    BoxGeometry::Params downBoxParams{params.width, params.height, 100};
    auto lowerBox = createBox(downBoxParams);
    lowerBox->position.y = -params.depth / 2 - downBoxParams.depth / 2;
    Box3 lowerHitBox;
    return lowerHitBox.setFromObject(*lowerBox);
}

auto createRightWorldEdge1(const BoxGeometry::Params params) {
    BoxGeometry::Params rightBoxParams{100, params.height, params.depth};
    auto rightBox = createBox(rightBoxParams);
    rightBox->position.x = params.width / 2 + rightBoxParams.width / 2;
    Box3 rightHitBox;
    return rightHitBox.setFromObject(*rightBox);
}

auto createLeftWorldEdge1(const BoxGeometry::Params params) {
    BoxGeometry::Params leftBoxParams{100, params.height, params.depth};
    auto leftBox = createBox(leftBoxParams);
    leftBox->position.x = -params.width / 2 - leftBoxParams.width / 2;
    Box3 leftHitBox;
    return leftHitBox.setFromObject(*leftBox);
}