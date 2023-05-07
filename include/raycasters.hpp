//
// Created by Jalma on 06/05/2023.
//

#ifndef TOP_GAME_RAYCASTERS_HPP
#define TOP_GAME_RAYCASTERS_HPP

#include "threepp/threepp.hpp"
#include <cmath>
#include <iostream>

class Raycasters{
public:
    threepp::Raycaster raycasterF;
    threepp::Raycaster raycaster90;
    threepp::Raycaster raycaster45;
    threepp::Raycaster raycastern45;
    threepp::Raycaster raycastern90;

    void updateRayCasterDirection(threepp::Vector3 origin, threepp::Vector2 direction, float objAngle){
        float angle = objAngle;
        threepp::Vector3 newDirection1{direction.y*std::sin(angle),direction.y*std::cos(angle),0};
        raycasterF.set(origin,newDirection1);
        angle += threepp::math::PI/4;
        threepp::Vector3 newDirection2{direction.y*std::sin(angle),direction.y*std::cos(angle),0};
        raycaster45.set(origin,newDirection2);
        angle += threepp::math::PI/4;
        threepp::Vector3 newDirection3{direction.y*std::sin(angle),direction.y*std::cos(angle),0};
        raycaster90.set(origin,newDirection3);
        angle -= 3*threepp::math::PI/4;
        threepp::Vector3 newDirection4{direction.y*std::sin(angle),direction.y*std::cos(angle),0};
        raycastern45.set(origin,newDirection4);
        angle -= threepp::math::PI/4;
        threepp::Vector3 newDirection5{direction.y*std::sin(angle),direction.y*std::cos(angle),0};
        raycastern90.set(origin,newDirection5);
    }

    threepp::Vector3 checkRayCasters(threepp::Object3D& scene, threepp::Vector3 direction){
        auto intersects1 = raycasterF.intersectObjects(scene.children);
        auto intersects2 = raycaster90.intersectObjects(scene.children);
        auto intersects3 = raycastern90.intersectObjects(scene.children);
        auto intersects4 = raycaster45.intersectObjects(scene.children);
        auto intersects5= raycastern45.intersectObjects(scene.children);


        if (!intersects1.empty()) {
            auto& intersect = intersects1.front();
            std::cout << " Forward: "<< intersect.point;
            std::cout << ", Normal: "<< intersect.face.value().normal;
            if (intersect.distance < 3){}
        }
       /* if (!intersects2.empty()) {
            auto& intersect = intersects2.front();
            std::cout << ", positive 90: "<<intersect.face.value().normal;
            if(intersect.distance < 3){
                intersect.face.value().normal
            }
        }
        if (!intersects4.empty()) {
            auto& intersect = intersects4.front();
            std::cout << ", positive 45: "<<intersect.distance;
        }
        if (!intersects3.empty()) {
            auto& intersect = intersects3.front();
            std::cout << ", negative 90: "<<intersect.distance;
        }
        if (!intersects5.empty()) {
            auto& intersect = intersects5.front();
            std::cout << ", negative 45: "<<intersect.distance<< std::endl;
        }
*/
        threepp::Vector3 newDirection;

        return newDirection;

    }

private:

};

#endif //TOP_GAME_RAYCASTERS_HPP
