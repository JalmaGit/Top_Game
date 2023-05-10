#ifndef TOP_GAME_GAME_HPP
#define TOP_GAME_GAME_HPP

#include <threepp/scenes/Scene.hpp>
#include <threepp/lights/HemisphereLight.hpp>
#include <threepp/math/Vector3.hpp>
#include "coin/coinLayer.hpp"
#include "spike/spikeLayer.hpp"
#include "world/worldLayer.hpp"
#include "player/player.hpp"
#include "player/playerCamera.hpp"
#include "player/playerVisualizer.hpp"
#include "player/cameraAttacher.hpp"
#include "raycasters.hpp"

class Game {
public:
    std::shared_ptr<threepp::Scene> scene;
    std::shared_ptr<threepp::HemisphereLight> light;

    explicit Game(float aspect);

    void running(threepp::Vector3 nextMove, float dt);

    PlayerCamera playerCamera;
    Player player;

private:
    CameraAttacher cameraCalculations;
    SpikeLayer spikeLayer;
    CoinLayer coinLayer;
    PlayerVisualizer playerVisualizer;
    WorldLayer worldScene;
    Raycasters raycasters{7};
};


#endif //TOP_GAME_GAME_HPP
