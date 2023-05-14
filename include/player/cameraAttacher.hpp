#ifndef TOP_GAME_CAMERAATTACHER_HPP
#define TOP_GAME_CAMERAATTACHER_HPP

#include <threepp/math/Vector3.hpp>
#include <threepp/math/Quaternion.hpp>
#include <threepp/math/MathUtils.hpp>
#include <cmath>

class CameraAttacher {
public:
    threepp::Quaternion quaternion;

    explicit CameraAttacher(threepp::Vector3 objPosition = {0, 0, 0},
                            float objAngle = 0);

    void setDistanceFromObj(float newDistanceFrom);

    void setPosition(threepp::Vector3 &position);

    void setCameraHeight(float newCameraHeight);

    void setCameraAngle(float newCameraAngle);

    void updateTrailingCamera(threepp::Vector3 &objPosition, float objAngle);

    threepp::Vector3 getPosition();

    [[nodiscard]] float getDistanceFromObj() const;

    [[nodiscard]] float getCameraAngle() const;

private:
    threepp::Vector3 position_;
    threepp::Vector3 upVector_;
    float distanceFrom_{};
    float cameraAngle_{};

};

#endif //TOP_GAME_CAMERAATTACHER_HPP
