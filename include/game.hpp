#ifndef TOP_GAME_GAME_HPP
#define TOP_GAME_GAME_HPP

#include <threepp/scenes/Scene.hpp>
#include <threepp/lights/SpotLight.hpp>
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

    PlayerCamera playerCamera;
    Player player;

    explicit Game(float aspect);

    void running(threepp::Vector3 &nextMove, float dt);

private:
    std::shared_ptr<threepp::SpotLight> spotLight_;

    CameraAttacher cameraAttacher_;
    SpikeLayer spikeLayer_;
    CoinLayer coinLayer_;
    PlayerVisualizer playerVisualizer_;
    WorldLayer worldScene_;
    Raycasters raycasters_;

    void setSpotLight();

    void resetPlayer();
};


#endif //TOP_GAME_GAME_HPP
