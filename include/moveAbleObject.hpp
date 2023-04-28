//
// Created by Jalma on 26/04/2023.
//

#ifndef TOP_GAME_MOVEABLEOBJECT_HPP
#define TOP_GAME_MOVEABLEOBJECT_HPP

#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"
#include <cmath>

using namespace threepp;

class MoveAbleObject {
public:
    Vector3 position;
    Quaternion rotation;
    const Vector3 upDirection{0, 0, 1};

    explicit MoveAbleObject(float posX = 0, float posY = 0, float posZ = 0, float r = 0)
            : rotation_(r) {

        position.set(posX, posY, posZ);
        setRotation(r);
    }

    void setRotation(float angle) {
        rotation_= angle;
        rotation.setFromAxisAngle(upDirection, angle);
    }

    void setPosition(Vector3 &pos) {
        position = pos;
    }

    [[nodiscard]] float getRotation() const{
        return rotation_;
    }

    [[nodiscard]] Vector3 getPosition() const {
        return position;
    }

    void move(float velocity, float turnSpeed){
        rotateBy(turnSpeed);
        moveFor(velocity);
    }


private:
    float rotation_;

    void rotateBy(float turnSpeed){
        rotation_ += turnSpeed;
        rotation.setFromAxisAngle(upDirection, rotation_);
    }

    void moveFor(float velocity){
        position += {velocity * std::cos(rotation_), velocity * std::sin(rotation_), 0};
    }

};

#endif //TOP_GAME_MOVEABLEOBJECT_HPP
