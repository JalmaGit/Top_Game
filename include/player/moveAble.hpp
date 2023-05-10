//
// Created by Jalma on 26/04/2023.
//

#ifndef TOP_GAME_MOVEABLE_HPP
#define TOP_GAME_MOVEABLE_HPP

#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"
#include <cmath>


class MoveAble {
public:
    threepp::Vector3 direction{};
    threepp::Vector3 position;
    threepp::Quaternion quaternion;
    const threepp::Vector3 upDirection{0, 0, 1};

    explicit MoveAble(threepp::Vector3 startPos = {0, 0, 0}, float angle = 0)
            : rotation_(angle) {

        position.copy(startPos);
        setRotation(angle);
        setBaseSpeed(50);
        setTurnSpeed(1);
    }

    void setForceVector(float velocity, float dt) {
        direction = {baseSpeed_ * velocity * std::sin(rotation_) * dt,
                     baseSpeed_ * velocity * std::cos(rotation_) * dt,
                     0};
    }

    void setRotation(float angle) {
        rotation_ = angle;
        quaternion.setFromAxisAngle(upDirection, angle);
    }

    void setPosition(threepp::Vector3 &pos) {
        position = pos;
    }

    void setBaseSpeed(float newBaseSpeed) {
        baseSpeed_ = newBaseSpeed;
    }

    void setTurnSpeed(float newTurnSpeed) {
        turnSpeed_ = newTurnSpeed;
    }

    [[nodiscard]] threepp::Vector3 getPosition() const {
        return position;
    }

    [[nodiscard]] float getRotation() const {
        return rotation_;
    }

    [[nodiscard]] float getBaseSpeed() const {
        return baseSpeed_;
    }

    [[nodiscard]] float getTurnSpeed() const {
        return turnSpeed_;
    }

    [[nodiscard]] threepp::Vector3 getDirection() const {
        return direction;
    }

    void move(float turnDirection, float dt) {
        rotateBy(turnDirection * dt);
        moveFor();
    }

    void resetPosAndRotation() {
        setPosition(resetPosition_);
        setRotation(resetRotation_);
    }

private:

    float rotation_;
    float baseSpeed_{};
    float turnSpeed_{};

    threepp::Vector3 resetPosition_{0, 0, 0};
    float resetRotation_{0};

    void rotateBy(float turnDirection) {
        rotation_ += turnSpeed_ * turnDirection;
        quaternion.setFromAxisAngle(upDirection, -rotation_);
    }

    void moveFor() {
        position += {direction.x,
                     direction.y,
                     0};
    }

};

#endif //TOP_GAME_MOVEABLE_HPP
