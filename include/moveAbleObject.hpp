//
// Created by Jalma on 26/04/2023.
//

#ifndef TOP_GAME_MOVEABLEOBJECT_HPP
#define TOP_GAME_MOVEABLEOBJECT_HPP

#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"

using namespace threepp;

class MoveAbleObject{
public:
    Vector3 position;
    Quaternion rotation;
    const Vector3 upDirection{0,0,1};

    auto setRotation(float& angle){
        rotation.setFromAxisAngle(upDirection,angle);
    }

    explicit MoveAbleObject(float x = 0, float y = 0, float z = 0, float r = math::PI / 2) : posX_(x),posY_(y),posZ_(z),rotation_(r){
        position.set(x,y,z);
        setRotation(r);
    }

    auto setPosition(Vector3& pos) const{
        pos.copy(position);
    }

    auto getPosition(Vector3& pos) const{
        pos.copy(position);
    }

private:
    float posX_;
    float posY_;
    float posZ_;
    float rotation_;

};

#endif //TOP_GAME_MOVEABLEOBJECT_HPP
