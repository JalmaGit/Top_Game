
#include "spike/spikeLayer.hpp"

SpikeLayer::SpikeLayer() {
    layer = threepp::Scene::create();

    MapFileReader file;
    file.read("data/mapSpikeData.txt");

    for (auto &it: file.mapData) {
        spikeMath.spikePositions.emplace_back(it.second.position);
    }

    SpikeVisualizer spikeVisualizer_;

    for (auto &element: spikeMath.spikePositions) {
        spikeVisualizer_.spikes.emplace_back(SpikeVisualizer::createSpike(element));
    }

    for (const auto &element: spikeVisualizer_.spikes) {
        layer->add(element);
    }
}
