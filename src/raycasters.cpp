
#include "raycasters.hpp"

Raycasters::Raycasters(int numberOfRayCasters, float originBaseSpeed) {
    totalNumberOfRayCasters_ = static_cast<float> (numberOfRayCasters);
    for (int i = 0; i < numberOfRayCasters; i++) {
        raycasters_.emplace_back(createRayCaster(originBaseSpeed));
    }
}

void Raycasters::updateRayCasterDirections(threepp::Vector3 origin, threepp::Vector3 direction, float objAngle) {
    float angle = objAngle;
    angle -= threepp::math::PI / 4;
    origin.z -= 1;
    for (auto &element: raycasters_) {
        threepp::Vector3 newDirection{direction.y * std::sin(angle),
                                      direction.y * std::cos(angle),
                                      0};
        element.set(origin, newDirection);
        angle += (threepp::math::PI / 2) / (totalNumberOfRayCasters_ - 1);
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

            if (intersect.distance < 3) {
                float w1 = (direction.x * intersect.face.value().normal.x
                            + direction.y * intersect.face.value().normal.z) /
                           (intersect.face.value().normal.x * intersect.face.value().normal.x +
                            intersect.face.value().normal.z * intersect.face.value().normal.z);
                threepp::Vector3 W1{intersect.face.value().normal.x * w1,
                                    intersect.face.value().normal.z * w1,
                                    0};

                threepp::Vector3 W2{
                        direction.x - W1.x, direction.y - W1.y, 0
                };
                direction.x = W2.x;
                direction.y = W2.y;
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
            if (intersect.distance < 3) {
                return true;
            }
        }
    }
    return false;
}

threepp::Raycaster Raycasters::createRayCaster(float originBaseSpeed) {
    threepp::Raycaster raycaster;
    raycaster.near = 0.1;
    raycaster.far = originBaseSpeed*2;
    return raycaster;
}
