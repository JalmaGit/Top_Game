//
// Created by Jalma on 29/04/2023.
//

#ifndef TOP_GAME_CAMERACALCULATIONS_HPP
#define TOP_GAME_CAMERACALCULATIONS_HPP

#include "moveAbleObject.hpp"

class CameraCalculations {
public:
    CameraCalculations (Vector3& objPosition, float objAngle){
        setDistanceFromObj(5);
        setTrailingCamera(objPosition, objAngle);
    }

    void setDistanceFromObj(float newDistanceFrom){
        distanceFrom_ = newDistanceFrom;
    }

    void setPosition(Vector3 position){
        position_ = position;
    }

    void setTrailingCamera(Vector3& objPosition, float objAngle){
        position_ = {sin(objAngle), cos(objAngle),0};
    }

    Vector3 getPosition(){
        return position_;
    }

    float getDistanceFromObj(){
        return distanceFrom_;
    }

private:
    Vector3 position_;
    float distanceFrom_;

};

#endif //TOP_GAME_CAMERACALCULATIONS_HPP
