#ifndef TOP_GAME_COINLAYER_HPP
#define TOP_GAME_COINLAYER_HPP

#include <threepp/scenes/Scene.hpp>
#include <threepp/math/Vector3.hpp>

#include "mapFileReader.hpp"
#include "coinMath.hpp"
#include "coinVisualizer.hpp"


class CoinLayer {
public:
    std::shared_ptr<threepp::Scene> layer;
    CoinMath coinMath;

    CoinLayer();

    void setRandomCoinPosition();

private:

    MapFileReader file;

    std::vector<threepp::Vector3> coinPositions_;

    CoinVisualizer coinVisualizer_;
};

#endif //TOP_GAME_COINLAYER_HPP
