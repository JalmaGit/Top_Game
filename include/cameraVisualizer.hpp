//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_CAMERAHANDLER_HPP
#define TOP_GAME_CAMERAHANDLER_HPP

#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/math/Quaternion.hpp"
#include "threepp/math/MathUtils.hpp"

using namespace threepp;

class CameraVisualizer { //kan dette testes?
public:

    std::shared_ptr<PerspectiveCamera> camera;

    CameraVisualizer (float aspect, float cameraAngle, Vector3 position){
        camera = PerspectiveCamera::create(75, aspect, 0.1f, 2000);
        camera->position = position;
        camera->rotateX(cameraAngle);
    }

    void updateCammeraPosition(Vector3 position, const Quaternion& quaternion, float cameraAngle) const{
        camera->position = position;
        camera->setRotationFromQuaternion(quaternion);
        camera->rotateX(cameraAngle);
    }

private:

};


#endif //TOP_GAME_CAMERAHANDLER_HPP
