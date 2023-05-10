
#include "spike/spikeLayer.hpp"

SpikeLayer::SpikeLayer() {
    layer = threepp::Scene::create();

    mapFileReader file;
    std::optional<std::string> fileRead = file.read("bin/data/mapSpikeData.txt");

    for (auto &it: file.mapData) {
        spikePositions_.emplace_back(it.second.Position);
    }

    SpikeVisualizer spikeVisualizer_{spikePositions_};

    for (const auto &element: spikeVisualizer_.spike) {
        layer->add(element);
    }
}
