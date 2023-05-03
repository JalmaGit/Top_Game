//
// Created by Jalma on 26/04/2023.
//

#ifndef TOP_GAME_MOVEABLEOBJECT_HPP
#define TOP_GAME_MOVEABLEOBJECT_HPP

#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"
#include <cmath>

using namespace threepp; //fyfy don't please

class MoveAbleObject {
public:

    Vector3 position;
    Quaternion quaternion;
    const Vector3 upDirection{0, 0, 1};

    //Rename to MoveAble

    explicit MoveAbleObject(Vector3 startPos = {0, 0, 0}, float angle = 0) //Husk å gå gjennom nanv i alt
            : rotation_(angle) {

        position.copy(startPos);
        setRotation(angle);
        setBaseSpeed(50);
        setTurnSpeed(1);
    }

    void setRotation(float angle) {
        rotation_ = angle;
        quaternion.setFromAxisAngle(upDirection, angle);
    }

    void setPosition(Vector3 &pos) {
        position = pos;
    }

    void setBaseSpeed(float newBaseSpeed) {
        baseSpeed_ = newBaseSpeed;
    }

    void setTurnSpeed(float newTurnSpeed) {
        turnSpeed_ = newTurnSpeed;
    }

    [[nodiscard]] const Vector3 getPosition() const {
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

    [[nodiscard]] Vector3 getDirection() {
        direction_ = {std::sin(rotation_), std::cos(rotation_), 0};
        return direction_;
    }

    void move(float velocity, float turnDirection) {
        rotateBy(turnDirection);
        moveFor(velocity);
    }

    void resetPosAndRotation() {
        setPosition(resetPosition_);
        setRotation(resetRotation_);
    }

private:
    Vector3 direction_{};
    float rotation_;
    float baseSpeed_{};
    float turnSpeed_{};

    Vector3 resetPosition_{0, 0, 0};
    float resetRotation_{0};

    void rotateBy(float turnDirection) {
        rotation_ += turnSpeed_ * turnDirection;
        quaternion.setFromAxisAngle(upDirection, -rotation_);
    }

//Husk code som ikke går utenfor skjermen
    void moveFor(float velocity) {
        position += {velocity * baseSpeed_ * std::sin(rotation_),
                     velocity * baseSpeed_ * std::cos(rotation_),
                     0};
    }

};

#endif //TOP_GAME_MOVEABLEOBJECT_HPP
