
#include "player/cameraAttacher.hpp"

CameraAttacher::CameraAttacher(threepp::Vector3 objPosition, float objAngle) { //Ask on Tuesday about this comment
    setDistanceFromObj(0);
    setPosition(objPosition);
    setCameraHeight(20);
    setCameraAngle(threepp::math::PI / 8);
    upVector_ = {0, 0, 1};
    updateTrailingCamera(objPosition, objAngle);
}

void CameraAttacher::setDistanceFromObj(float newDistanceFrom) {
    distanceFrom_ = -newDistanceFrom;
}

void CameraAttacher::setPosition(threepp::Vector3 &position) {
    position_ = position;
}

void CameraAttacher::setCameraHeight(float newCameraHeight) {
    position_.z = newCameraHeight;
}

void CameraAttacher::setCameraAngle(float newCameraAngle) {
    cameraAngle_ = newCameraAngle;
}

void CameraAttacher::updateTrailingCamera(threepp::Vector3 &objPosition, float objAngle) {
    quaternion.setFromAxisAngle(upVector_, objAngle);
    position_ = {distanceFrom_ * std::sin(objAngle) + objPosition.x,
                 distanceFrom_ * std::cos(objAngle) + objPosition.y, position_.z};
}

threepp::Vector3 CameraAttacher::getPosition() {
    return position_;
}

float CameraAttacher::getDistanceFromObj() const {
    return distanceFrom_;
}

float CameraAttacher::getCameraAngle() const {
    return cameraAngle_;
}
