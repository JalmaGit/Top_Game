//
// Created by Jalma on 06/05/2023.
//

#ifndef TOP_GAME_RAYCASTERS_HPP
#define TOP_GAME_RAYCASTERS_HPP

#include "threepp/threepp.hpp"
#include <cmath>
#include <iostream>

class Raycasters {
public:
    std::vector<threepp::Raycaster> raycasters;

    explicit Raycasters (int numberOfRayCasters){
        totalNumberOfRayCasters = static_cast<float> (numberOfRayCasters);
        for (int i = 0; i < numberOfRayCasters; i++){
            raycasters.emplace_back(createRayCaster());
        }

    }

    static threepp::Raycaster createRayCaster(){
        threepp::Raycaster raycaster;
        return raycaster;
    }


    void updateRayCasterDirections(threepp::Vector3 origin, threepp::Vector2 direction, float objAngle){
        float angle = objAngle;
        angle -= threepp::math::PI/4;
        for (auto& element : raycasters){
            threepp::Vector3 newDirection{direction.y * std::sin(angle), direction.y * std::cos(angle), 0};
            element.set(origin, newDirection);
            angle += (threepp::math::PI/2)/(totalNumberOfRayCasters-1);
        }
    }

    void checkMovement(threepp::Object3D &scene, threepp::Vector3 &direction){
        std::vector<std::vector<threepp::Intersection>> intersections;
        intersections.reserve(raycasters.size());
        for (auto& element : raycasters){
            intersections.emplace_back(element.intersectObjects(scene.children));
        }

        for (auto& element : intersections){

            if (!element.empty()) {
                auto &intersect = element.front();

                if (intersect.distance < 3) {
                    float w1 = (direction.x*intersect.face.value().normal.x
                                + direction.y*intersect.face.value().normal.z)/
                               (intersect.face.value().normal.x*intersect.face.value().normal.x +
                                intersect.face.value().normal.z*intersect.face.value().normal.z) ;
                    threepp::Vector3 W1{intersect.face.value().normal.x*w1,intersect.face.value().normal.z*w1,0};

                    threepp::Vector3 W2{
                            direction.x-W1.x,direction.y-W1.y,0
                    };
                    direction.x = W2.x;
                    direction.y = W2.y;
                }
            }
        }
    }

private:
    float totalNumberOfRayCasters;

};

#endif //TOP_GAME_RAYCASTERS_HPP
