//
// Created by Jalma on 29/04/2023.
//

#ifndef TOP_GAME_CAMERACALCULATIONS_HPP
#define TOP_GAME_CAMERACALCULATIONS_HPP

#include "moveAbleObject.hpp"

class cameraCalculations {
public:
    cameraCalculations(){

    }

    void setPosition(Vector3 position){
        position_ = position;
    }

    void attachToObject(Vector3 objPosition, float objAngle){
        position_ = {sin(objAngle), cos(objAngle),0};
    }

    Vector3 getPosition(){
        return position_;
    }

private:
    Vector3 position_;


};

#endif //TOP_GAME_CAMERACALCULATIONS_HPP
