//
// Created by Jalma on 29/04/2023.
//

#ifndef TOP_GAME_CAMERAATTACHER_HPP
#define TOP_GAME_CAMERAATTACHER_HPP

#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"
#include <cmath>

class CameraAttacher {
public:
    threepp::Quaternion quaternion;

    explicit CameraAttacher(threepp::Vector3 objPosition = {0, 0, 0}, float objAngle = 0) { //Ask on Tuesday about this comment
        setDistanceFromObj(5);
        setPosition({0, 0, 0});
        setCameraHeight(5);
        setCameraAngle(threepp::math::PI / 3);
        upVector_ = {0, 0, 1};
        updateTrailingCamera(objPosition, objAngle);
    }

    void setDistanceFromObj(float newDistanceFrom) {
        distanceFrom_ = -newDistanceFrom;
    }

    void setPosition(threepp::Vector3 position) {
        position_ = position;
    }

    void setCameraHeight(float newCameraHeight) {
        position_.z = newCameraHeight;
    }

    void setCameraAngle(float newCameraAngle) {
        cameraAngle_ = newCameraAngle;
    }

    void updateTrailingCamera(threepp::Vector3 objPosition, float objAngle) {
        quaternion.setFromAxisAngle(upVector_, objAngle);
        position_ = {distanceFrom_ * std::sin(objAngle) + objPosition.x,
                     distanceFrom_ * std::cos(objAngle) + objPosition.y, position_.z};
    }

    threepp::Vector3 getPosition() {
        return position_;
    }

    [[nodiscard]] float getDistanceFromObj() const {
        return distanceFrom_;
    }

    [[nodiscard]] float getCameraAngle() const {
        return cameraAngle_;
    }

private:
    threepp::Vector3 position_;
    threepp::Vector3 upVector_;
    float distanceFrom_{};
    float cameraAngle_{};

};

#endif //TOP_GAME_CAMERAATTACHER_HPP
