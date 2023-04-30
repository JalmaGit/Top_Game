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

class CameraHandler { //kan dette testes?
public:

    std::shared_ptr<PerspectiveCamera> camera;

    CameraHandler (){
        camera = PerspectiveCamera::create();
    }

    auto setCammeraPosition(Vector3& position, Quaternion rotation, float cameraAngle) const{

    }

private:


};


#endif //TOP_GAME_CAMERAHANDLER_HPP
