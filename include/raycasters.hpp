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

    explicit Raycasters (int numberOfRayCasters){
        totalNumberOfRayCasters_ = static_cast<float> (numberOfRayCasters);
        for (int i = 0; i < numberOfRayCasters; i++){
            raycasters_.emplace_back(createRayCaster());
        }
    }

    void updateRayCasterDirections(threepp::Vector3 origin, threepp::Vector3 direction, float objAngle){
        float angle = objAngle;
        angle -= threepp::math::PI/4;
        for (auto& element : raycasters_){
            threepp::Vector3 newDirection{direction.y * std::sin(angle), direction.y * std::cos(angle), 0};
            element.set(origin, newDirection);
            angle += (threepp::math::PI/2)/(totalNumberOfRayCasters_ - 1);
        }
    }

    void checkForWalls(threepp::Object3D &scene, threepp::Vector3 &direction){
        std::vector<std::vector<threepp::Intersection>> intersections;
        intersections.reserve(raycasters_.size());
        for (auto& element : raycasters_){
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

   bool checkForInteractable(threepp::Object3D &scene){
        std::vector<std::vector<threepp::Intersection>> intersections;
        intersections.reserve(raycasters_.size());
        for (auto& element : raycasters_){
            intersections.emplace_back(element.intersectObjects(scene.children));
        }

        for (auto& element : intersections){

            if (!element.empty()) {
                auto &intersect = element.front();
                if (intersect.distance < 3) {
                    return true;
                }
            }
        }
        return false;
    }

private:

    std::vector<threepp::Raycaster> raycasters_;
    float totalNumberOfRayCasters_;

    static threepp::Raycaster createRayCaster(){
        threepp::Raycaster raycaster;
        raycaster.near = 0.1;
        raycaster.far = 100;
        return raycaster;
    }


};

#endif //TOP_GAME_RAYCASTERS_HPP
