
#include "world/worldLayer.hpp"

WorldLayer::WorldLayer() {

    layer = threepp::Scene::create();

    MapFileReader file;
    file.read("data/mapWallData.txt");

    WorldVisualizer worldVisualizer{500, 500};

    for (auto &it: file.mapData) {
        worldVisualizer.addBox(it.second.Position, it.second.Size);
    }

    for (const auto &element: worldVisualizer.boxes) {
        layer->add(element);
    }

    layer->add(worldVisualizer.flor);
}
