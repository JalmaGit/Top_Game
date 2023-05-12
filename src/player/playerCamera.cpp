#include "player/playerCamera.hpp"

PlayerCamera::PlayerCamera(float aspect, float cameraAngle, threepp::Vector3 position) {
    camera = threepp::PerspectiveCamera::create(75, aspect, 0.1f, 100);
    camera->position = position;
    camera->rotateX(cameraAngle);
}

void PlayerCamera::updateCameraPosition(const threepp::Vector3& position, const threepp::Quaternion &quaternion,
                                        float cameraAngle) const {
    camera->position = position;
    camera->setRotationFromQuaternion(quaternion);
    camera->rotateX(cameraAngle);
}


