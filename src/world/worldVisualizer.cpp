
#include "world/worldVisualizer.hpp"
#include "threepp/loaders/TextureLoader.hpp"
#include "threepp/geometries/PlaneGeometry.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"
#include "threepp/geometries/BoxGeometry.hpp"
#include "threepp/math/MathUtils.hpp"

using namespace threepp; //This is fine bc this is cpp file or source file

WorldVisualizer::WorldVisualizer(float mapSizeX, float mapSizeY) {
    flor = createPlane(mapSizeX, mapSizeY);
}

void WorldVisualizer::addBox(threepp::Vector3 boxPosition, threepp::Vector3 boxSize) {
    boxes.emplace_back(createBox(boxPosition, boxSize));
}

std::shared_ptr<Mesh> WorldVisualizer::createPlane(float width, float length) {
    TextureLoader loader;

    auto planeGeometry = PlaneGeometry::create(width, length);
    auto planeMaterial = MeshPhongMaterial::create();
    //planeMaterial->map = loader.load("bin/data/textures/flor.png");

    planeMaterial->color.setHex(Color::grey);
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);

    plane->receiveShadow = true;

    return plane;
}

std::shared_ptr<Mesh> WorldVisualizer::createBox(Vector3 boxPosition, Vector3 boxSize) {

    auto boxGeometry = BoxGeometry::create(
            boxSize.x,
            boxSize.y,
            boxSize.z);

    auto boxMaterial = MeshPhongMaterial::create();
    boxMaterial->color = 0xff0000;
    boxMaterial->emissive = 0x000000;

    auto box = Mesh::create(boxGeometry, boxMaterial);
    box->position = boxPosition;
    box->rotateX(threepp::math::PI / 2);

    box->castShadow = true;

    return box;
}




