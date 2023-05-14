#ifndef TOP_GAME_SPIKELAYER_HPP
#define TOP_GAME_SPIKELAYER_HPP

#include <threepp/scenes/Scene.hpp>
#include <threepp/math/Vector3.hpp>
#include "mapFileReader.hpp"
#include "spike/spikeMath.hpp"
#include "spikeVisualizer.hpp"

class SpikeLayer {
public:
    std::shared_ptr<threepp::Scene> layer;
    SpikeMath spikeMath;

    SpikeLayer();

private:
    std::vector<threepp::Vector3> spikePositions_;
};

#endif //TOP_GAME_SPIKELAYER_HPP
