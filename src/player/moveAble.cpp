#include "player/moveAble.hpp"

MoveAble::MoveAble(threepp::Vector3 startPos, float angle)
        : rotation_(angle) {

    position.copy(startPos);
    setRotation(angle);
    setBaseSpeed(50);
    setTurnSpeed(1);
}

void MoveAble::setForceVector(float velocity, float dt) {
    direction = {baseSpeed_ * velocity * std::sin(rotation_) * dt,
                 baseSpeed_ * velocity * std::cos(rotation_) * dt,
                 0};
}

void MoveAble::setRotation(float angle) {
    rotation_ = angle;
    quaternion.setFromAxisAngle(upDirection, angle);
}

void MoveAble::setPosition(threepp::Vector3 &pos) {
    position = pos;
}

void MoveAble::setBaseSpeed(float newBaseSpeed) {
    baseSpeed_ = newBaseSpeed;
}

void MoveAble::setTurnSpeed(float newTurnSpeed) {
    turnSpeed_ = newTurnSpeed;
}

threepp::Vector3 MoveAble::getPosition() const {
    return position;
}

float MoveAble::getRotation() const {
    return rotation_;
}

float MoveAble::getBaseSpeed() const {
    return baseSpeed_;
}

float MoveAble::getTurnSpeed() const {
    return turnSpeed_;
}

threepp::Vector3 MoveAble::getDirection() const {
    return direction;
}

void MoveAble::move(float turnDirection, float dt) {
    rotateBy(turnDirection * dt);
    moveFor();
}

void MoveAble::resetPosAndRotation() {
    setPosition(resetPosition_);
    setRotation(resetRotation_);
}

void MoveAble::rotateBy(float turnDirection) {
    rotation_ += turnSpeed_ * turnDirection;
    quaternion.setFromAxisAngle(upDirection, -rotation_);
}

void MoveAble::moveFor() {
    position += {direction.x,
                 direction.y,
                 0};
}
