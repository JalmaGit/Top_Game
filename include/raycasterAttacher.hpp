//
// Created by Jalma on 05/05/2023.
//

#ifndef TOP_GAME_RAYCASTERATTACHER_HPP
#define TOP_GAME_RAYCASTERATTACHER_HPP

#include <threepp/math/Vector3.hpp>

class RaycasterAttacher {
public:

    RaycasterAttacher(threepp::Vector3 objPosition) {
        setFromOrigin(objPosition);
    }

    void updateRaycaster(threepp::Vector3 newObjectPosition, threepp::Vector3 objectDirection){
        setFromOrigin(newObjectPosition);
    }

    void checkNextMove(){

    }

private:



    void setFromOrigin(threepp::Vector3 newOrigin) {
        origin = newOrigin;
    }

    threepp::Vector3 origin;
};


#endif //TOP_GAME_RAYCASTERATTACHER_HPP
