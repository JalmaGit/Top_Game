//
// Created by Jalma on 28/04/2023.
//

#ifndef TOP_GAME_CAMERAHANDLER_HPP
#define TOP_GAME_CAMERAHANDLER_HPP

#include ""

class CameraHandler { //kan dette testes?
public:

    explicit CameraHandler(){

    }

    auto setCammeraPosition(Vector3& position, Quaternion rotation) const{
        playerModel->position.copy(position);
        playerModel->rotation.setFromQuaternion(rotation);
    }

private:

};


#endif //TOP_GAME_CAMERAHANDLER_HPP
