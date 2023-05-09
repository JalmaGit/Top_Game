//
// Created by Jalma on 09/05/2023.
//

#ifndef TOP_GAME_WORLDLAYER_HPP
#define TOP_GAME_WORLDLAYER_HPP

#include "threepp/scenes/Scene.hpp"
#include "threepp/lights/HemisphereLight.hpp"
#include "mapFileReader.hpp"
#include "worldVisualizer.hpp"


class WorldLayer {
public:
    std::shared_ptr<threepp::Scene> layer;

    WorldLayer(){

        layer = threepp::Scene::create();

        mapFileReader file;
        std::optional<std::string> fileRead = file.read("bin/data/mapWallData.txt");

        WorldVisualizer worldVisualizer{500, 500};

        for (auto& it: file.mapData) {
            worldVisualizer.addBox(it.second.Position,it.second.Size);
        }

        for (const auto& element : worldVisualizer.boxes){
            layer->add(element);
        }

        layer->add(worldVisualizer.flor);
    }
};


#endif //TOP_GAME_WORLDLAYER_HPP
