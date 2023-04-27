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

    explicit MoveAbleObject(float x = 0, float y = 0, float z = 0, float r = 0)
            : posX_(x), posY_(y), posZ_(z), rotation_(r) {

        position.set(x, y, z);
        setRotation(r);
    }

    void setRotation(float angle) {
        rotation_=angle;
        rotation.setFromAxisAngle(upDirection, angle);
    }

    void setPosition(Vector3 &pos) {
        move(pos);
    }

    Vector3 getPosition() const {
        return position;
    }

    void move(Vector3& vector3){
        position.y += vector3.x*std::sin(rotation_);
        position.x += vector3.x*std::cos(rotation_);
    }

private:
    float posX_;
    float posY_;
    float posZ_;
    float rotation_;

};

#endif //TOP_GAME_MOVEABLEOBJECT_HPP
