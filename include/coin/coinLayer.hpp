//
// Created by Jalma on 09/05/2023.
//

#ifndef TOP_GAME_COINLAYER_HPP
#define TOP_GAME_COINLAYER_HPP

#include "threepp/scenes/Scene.hpp"
#include "threepp/math/Vector3.hpp"
#include "mapFileReader.hpp"
#include "coinMath.hpp"
#include "coinVisualizer.hpp"


class CoinLayer {
public:
    std::shared_ptr<threepp::Scene> layer;

    CoinLayer(){
        layer = threepp::Scene::create();

        mapFileReader file;
        std::optional<std::string> fileRead = file.read("bin/data/mapCoinData.txt");

        for (auto& element : file.mapData){
            coinPositions.emplace_back(element.second.Position);
        }

        coinMath_.setPossiblePositions(coinPositions);

        layer->add(coinVisualizer_.coin);
    }

    void setRandomCoinPosition(){
        coinVisualizer_.updateCoinPosition(coinMath_.getRandomNewPosition());
    }

private:

    std::vector<threepp::Vector3> coinPositions;
    CoinMath coinMath_;
    CoinVisualizer coinVisualizer_;
};



#endif //TOP_GAME_COINLAYER_HPP
