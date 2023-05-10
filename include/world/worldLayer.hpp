#ifndef TOP_GAME_WORLDLAYER_HPP
#define TOP_GAME_WORLDLAYER_HPP

#include <threepp/scenes/Scene.hpp>
#include <threepp/lights/HemisphereLight.hpp>
#include "mapFileReader.hpp"
#include "worldVisualizer.hpp"


class WorldLayer {
public:
    std::shared_ptr<threepp::Scene> layer;

    WorldLayer();
};


#endif //TOP_GAME_WORLDLAYER_HPP
