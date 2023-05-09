//
// Created by Jalma on 09/05/2023.
//

#ifndef TOP_GAME_SPIKELAYER_HPP
#define TOP_GAME_SPIKELAYER_HPP

#include "threepp/scenes/Scene.hpp"
#include "threepp/math/Vector3.hpp"
#include <utility>
#include "mapFileReader.hpp"
#include "spike/spikeMath.hpp"
#include "spikeVisualizer.hpp"

class SpikeLayer {
public:
    std::shared_ptr<threepp::Scene> layer;
    SpikeMath spikeMath_;

    SpikeLayer() {
        layer = threepp::Scene::create();

        mapFileReader file;
        std::optional<std::string> fileRead = file.read("bin/data/mapSpikeData.txt");

        for (auto& it: file.mapData) {
            spikePositions_.emplace_back(it.second.Position);
        }

        SpikeVisualizer spikeVisualizer_{spikePositions_};

        for (const auto& element : spikeVisualizer_.spike){
            layer->add(element);
        }
    }

private:
    std::vector<threepp::Vector3> spikePositions_;
};

#endif //TOP_GAME_SPIKELAYER_HPP
