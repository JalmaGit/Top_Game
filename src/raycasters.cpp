
#include <threepp/math/MathUtils.hpp>
#include "raycasters.hpp"

Raycasters::Raycasters(int numberOfRayCasters, float originBaseSpeed) {
    totalNumberOfRayCasters_ = static_cast<float> (numberOfRayCasters);
    for (int i = 0; i < numberOfRayCasters; i++) {
        raycasters_.emplace_back(createRayCaster(originBaseSpeed));
    }
}

void Raycasters::updateRayCasterDirections(threepp::Vector3 &origin,
                                           threepp::Vector3 &direction,
                                           float objAngle) {
    float angle = objAngle;
    angle -= threepp::math::PI / 4.0f;
    for (auto &element: raycasters_) {
        threepp::Vector3 newDirection{direction.y * std::sin(angle),
                                      direction.y * std::cos(angle),
                                      0};
        element.set({origin.x,origin.y,origin.z-1.0f}, newDirection);
        angle += (threepp::math::PI / 2.0f) / (totalNumberOfRayCasters_ - 1.0f);
    }
}

void Raycasters::checkForCollisionStep(threepp::Object3D &scene, threepp::Vector3 &direction) {
    std::vector<std::vector<threepp::Intersection>> intersections;
    intersections.reserve(raycasters_.size());
    for (auto &element: raycasters_) {
        intersections.emplace_back(element.intersectObjects(scene.children));
    }

    for (auto &element: intersections) {

        if (!element.empty()) {
            auto &intersect = element.front();

            if (intersect.distance < 3.5f) {  //Calculating Projection Vector
                float vectorw1 = (direction.x * intersect.face.value().normal.x
                                  + direction.y * intersect.face.value().normal.z) /
                                 (intersect.face.value().normal.x * intersect.face.value().normal.x +
                                  intersect.face.value().normal.z * intersect.face.value().normal.z);

                threepp::Vector3 vectorW1{intersect.face.value().normal.x * vectorw1,
                                          intersect.face.value().normal.z * vectorw1,
                                          0.0f};

                threepp::Vector3 vectorW2{
                        direction.x - vectorW1.x, direction.y - vectorW1.y, 0.0f
                };
                direction.x = vectorW2.x;
                direction.y = vectorW2.y;
            }
        }
    }
}

bool Raycasters::checkForInteractableStep(threepp::Object3D &scene) {
    std::vector<std::vector<threepp::Intersection>> intersections;
    intersections.reserve(raycasters_.size());
    for (auto &element: raycasters_) {
        intersections.emplace_back(element.intersectObjects(scene.children));
    }

    for (auto &element: intersections) {

        if (!element.empty()) {
            auto &intersect = element.front();
            if (intersect.distance < 3.5f) {
                return true;
            }
        }
    }
    return false;
}

threepp::Raycaster Raycasters::createRayCaster(float originBaseSpeed) {
    threepp::Raycaster raycaster;
    raycaster.near = 0.1f;
    raycaster.far = originBaseSpeed * 2.0f;
    return raycaster;
}
