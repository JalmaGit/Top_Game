//
// Created by Jalma on 29/04/2023.
//

#ifndef TOP_GAME_CAMERACALCULATIONS_HPP
#define TOP_GAME_CAMERACALCULATIONS_HPP

#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"

using namespace threepp;

class CameraCalculations {
public:
    Quaternion quaternion;

    explicit CameraCalculations (Vector3 objPosition = {0,0,0}, float objAngle = 0){ //Ask on Tuesday about this comment
        setDistanceFromObj(5);
        setPosition({0,0,0});
        setCameraHeight(5);
        setCameraAngle(math::PI/4);
        upVector_ = {0,0,1};
        updateTrailingCamera(objPosition, objAngle);
    }

    void setDistanceFromObj(float newDistanceFrom){
        distanceFrom_ = -newDistanceFrom;
    }

    void setPosition(Vector3 position){
        position_ = position;
    }

    void setCameraHeight (float newCameraHeight){
        position_.z = newCameraHeight;
    }

    void setCameraAngle(float newCameraAngle){
        cameraAngle_ = newCameraAngle;
    }

    void updateTrailingCamera(Vector3 objPosition, float objAngle){
        quaternion.setFromAxisAngle(upVector_,objAngle);
        position_ = {distanceFrom_*sin(objAngle)+objPosition.x, distanceFrom_*cos(objAngle)+objPosition.y, position_.z};
    }

    Vector3 getPosition(){
        return position_;
    }

    [[nodiscard]] float getDistanceFromObj() const{
        return distanceFrom_;
    }

    [[nodiscard]] float getCameraAngle() const{
        return cameraAngle_;
    }

private:
    Vector3 position_;
    Vector3 upVector_;
    float distanceFrom_{};
    float cameraAngle_{};

};

#endif //TOP_GAME_CAMERACALCULATIONS_HPP
