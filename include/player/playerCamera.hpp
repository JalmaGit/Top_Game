#ifndef TOP_GAME_CAMERAHANDLER_HPP
#define TOP_GAME_CAMERAHANDLER_HPP

#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/math/Quaternion.hpp>
#include <threepp/math/MathUtils.hpp>

class PlayerCamera {
public:
    std::shared_ptr<threepp::PerspectiveCamera> camera;

    explicit PlayerCamera(float aspect = 60, float cameraAngle = 0, threepp::Vector3 position = {0, 0, 0});

    void updateCameraPosition(threepp::Vector3 position,
                              const threepp::Quaternion &quaternion,
                              float cameraAngle) const;
};



#endif //TOP_GAME_CAMERAHANDLER_HPP
