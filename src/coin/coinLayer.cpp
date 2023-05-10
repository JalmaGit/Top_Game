
#include "coin/coinLayer.hpp"

CoinLayer::CoinLayer() {
    layer = threepp::Scene::create();

    mapFileReader file;
    std::optional<std::string> fileRead = file.read("bin/data/mapCoinData.txt");

    for (auto &element: file.mapData) {
        coinPositions.emplace_back(element.second.Position);
    }

    coinMath.setPossiblePositions(coinPositions);

    layer->add(coinVisualizer_.coin);
}

void CoinLayer::setRandomCoinPosition() {
    coinVisualizer_.updateCoinPosition(coinMath.getRandomNewPosition());
}
