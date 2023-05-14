#ifndef TOP_GAME_SPIKELAYER_HPP
#define TOP_GAME_SPIKELAYER_HPP

#include <threepp/scenes/Scene.hpp>

#include "mapFileReader.hpp"
#include "spike/spikeMath.hpp"
#include "spikeVisualizer.hpp"

class SpikeLayer {
public:
    std::shared_ptr<threepp::Scene> layer;
    SpikeMath spikeMath;

    SpikeLayer();
};

#endif //TOP_GAME_SPIKELAYER_HPP
