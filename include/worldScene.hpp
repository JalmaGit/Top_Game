//
// Created by Jalma on 09/05/2023.
//

#ifndef TOP_GAME_WORLDSCENE_HPP
#define TOP_GAME_WORLDSCENE_HPP

#include <threepp/scenes/Scene.hpp>
#include <threepp/lights/HemisphereLight.hpp>
#include "keyInput.hpp"
#include "playerHandler.hpp"
#include "mapFileReader.hpp"
#include "worldVisualizer.hpp"


class WorldScene {
public:
    std::shared_ptr<threepp::Scene> scene;

    WorldScene(){

        scene = threepp::Scene::create();

        auto light = threepp::HemisphereLight::create();
        light->intensity = 0.7f;
        scene->add(light);

        mapFileReader file;
        std::optional<std::string> fileRead = file.read("bin/data/mapdata.txt");

        WorldVisualizer worldVisualizer{500, 500};

        for (auto& it: file.mapData) {
            worldVisualizer.addBox(it.second.Position,it.second.Size);
        }

        for (const auto& element : worldVisualizer.boxes){
            scene->add(element);
        }

        scene->add(worldVisualizer.flor);
    }
};


#endif //TOP_GAME_WORLDSCENE_HPP
