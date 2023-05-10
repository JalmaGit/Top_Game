#ifndef TOP_GAME_RAYCASTERS_HPP
#define TOP_GAME_RAYCASTERS_HPP

#include <threepp/math/Vector3.hpp>
#include <threepp/core/Raycaster.hpp>
#include <threepp/core/Object3D.hpp>
#include <threepp/math/MathUtils.hpp>
#include <cmath>
#include <iostream>

class Raycasters {
public:

    explicit Raycasters(int numberOfRayCasters);

    void updateRayCasterDirections(threepp::Vector3 origin, threepp::Vector3 direction, float objAngle);

    void checkForCollisionStep(threepp::Object3D &scene, threepp::Vector3 &direction);

    bool checkForInteractableStep(threepp::Object3D &scene);

private:

    std::vector<threepp::Raycaster> raycasters_;
    float totalNumberOfRayCasters_;

    static threepp::Raycaster createRayCaster();
};

#endif //TOP_GAME_RAYCASTERS_HPP
