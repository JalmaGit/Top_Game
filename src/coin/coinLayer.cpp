
#include "coin/coinLayer.hpp"

CoinLayer::CoinLayer() {
    layer = threepp::Scene::create();

    file.read("data/mapCoinData.txt");

    for (auto &element: file.mapData) {
        coinPositions_.emplace_back(element.second.position);
    }

    coinMath.setPossiblePositions(coinPositions_);

    layer->add(coinVisualizer_.coin);
}

void CoinLayer::setRandomCoinPosition() {
    coinVisualizer_.updateCoinPosition(coinMath.getNewPosition());
}
