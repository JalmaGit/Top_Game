#ifndef TOP_GAME_WORLDCALCULATIONS_HPP
#define TOP_GAME_WORLDCALCULATIONS_HPP

#include <threepp/objects/Mesh.hpp>
#include <threepp/math/Vector3.hpp>
#include <memory>

class WorldVisualizer {
public:

    std::shared_ptr<threepp::Mesh> flor;
    std::vector<std::shared_ptr<threepp::Mesh>> boxes;

    WorldVisualizer(float mapSizeX, float mapSizeY);

    void addBox(threepp::Vector3 &boxPosition, threepp::Vector3 &boxSize);

private:
    float mapSizeX_;
    float mapSizeY_;

    static std::shared_ptr<threepp::Mesh> createPlane(float width, float length);

    std::shared_ptr<threepp::Mesh> createBox(threepp::Vector3 &boxPosition, threepp::Vector3 &boxSize) const;

};

#endif //TOP_GAME_WORLDCALCULATIONS_HPP
