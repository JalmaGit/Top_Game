//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_CAMERAHANDLER_HPP
#define TOP_GAME_CAMERAHANDLER_HPP

#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"

class PlayerCamera { //CameraAttacher
public:
    std::shared_ptr<threepp::PerspectiveCamera> camera;

    PlayerCamera(float aspect = 60, float cameraAngle = 0, threepp::Vector3 position = {0,0,0}) {
        camera = threepp::PerspectiveCamera::create(75, aspect, 0.1f, 2000);
        camera->position = position;
        camera->rotateX(cameraAngle);
    }

    void updateCameraPosition(threepp::Vector3 position, const threepp::Quaternion &quaternion, float cameraAngle) const;
};

void PlayerCamera::updateCameraPosition(threepp::Vector3 position, const threepp::Quaternion &quaternion, float cameraAngle) const {
    camera->position = position;
    camera->setRotationFromQuaternion(quaternion);
    camera->rotateX(cameraAngle);
}

#endif //TOP_GAME_CAMERAHANDLER_HPP
