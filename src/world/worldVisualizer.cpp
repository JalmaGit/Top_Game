
#include <world/worldVisualizer.hpp>
#include <threepp/loaders/TextureLoader.hpp>
#include <threepp/geometries/PlaneGeometry.hpp>
#include <threepp/materials/MeshPhongMaterial.hpp>
#include <threepp/geometries/BoxGeometry.hpp>
#include <threepp/math/MathUtils.hpp>
#include <cmath>

WorldVisualizer::WorldVisualizer(float mapSizeX, float mapSizeY) :
        mapSizeX_(mapSizeX), mapSizeY_(mapSizeY) {
    flor = createPlane(mapSizeX, mapSizeY);
}

void WorldVisualizer::addBox(threepp::Vector3 &boxPosition, threepp::Vector3 &boxSize) {

    //Splits what would have been one box into two if necessary.
    //such that the colors match the correct quadrant within a normal x,y coordinate system
    if (boxPosition.x == 0.0) {
        threepp::Vector3 newPosition1{boxSize.x / 4, boxPosition.y, boxPosition.z};
        threepp::Vector3 newPosition2{-boxSize.x / 4, boxPosition.y, boxPosition.z};
        threepp::Vector3 newSize{boxSize.x / 2, boxSize.y, boxSize.z};

        boxes.emplace_back(createBox(newPosition1, newSize));
        boxes.emplace_back(createBox(newPosition2, newSize));
    } else if (boxPosition.y == 0.0) {
        threepp::Vector3 newPosition1{boxPosition.x, boxSize.z / 4, boxPosition.z};
        threepp::Vector3 newPosition2{boxPosition.x, -boxSize.z / 4, boxPosition.z};
        threepp::Vector3 newSize{boxSize.x, boxSize.y, boxSize.z / 2};

        boxes.emplace_back(createBox(newPosition1, newSize));
        boxes.emplace_back(createBox(newPosition2, newSize));
    } else {
        boxes.emplace_back(createBox(boxPosition, boxSize));
    }
}

std::shared_ptr<threepp::Mesh> WorldVisualizer::createPlane(float width, float length) {
    threepp::TextureLoader loader;

    auto planeGeometry = threepp::PlaneGeometry::create(width, length);
    auto planeMaterial = threepp::MeshPhongMaterial::create();

    planeMaterial->color.setHex(0xC1C1C1); //Lighter grey
    planeMaterial->side = threepp::DoubleSide;
    auto plane = threepp::Mesh::create(planeGeometry, planeMaterial);

    plane->receiveShadow = true;

    return plane;
}

std::shared_ptr<threepp::Mesh>WorldVisualizer::createBox(
        threepp::Vector3 &boxPosition, threepp::Vector3 &boxSize) const {

    auto boxGeometry = threepp::BoxGeometry::create(
            boxSize.x,
            boxSize.y,
            boxSize.z);

    auto boxMaterial = threepp::MeshPhongMaterial::create();

    if (boxPosition.x < 0 && boxPosition.y < 0) {
        boxMaterial->color = 0xfff000; //Yellow
    } else if (boxPosition.x > 0 && boxPosition.y < 0) {
        boxMaterial->color = 0x0000ff; //Blue
    } else if (boxPosition.x < 0 && boxPosition.y > 0) {
        boxMaterial->color = 0x00ff00; //Green
    } else if (boxPosition.x > 0 && boxPosition.y > 0) {
        boxMaterial->color = 0xff0000; //Red
    }

    if (std::abs(boxPosition.x) >= mapSizeX_ / 2 ||
        std::abs(boxPosition.y) >= mapSizeY_ / 2) {
        boxMaterial->color = 0x545454; //Darker grey
    }

    auto box = threepp::Mesh::create(boxGeometry, boxMaterial);
    box->position = boxPosition;
    box->rotateX(threepp::math::PI / 2);
    box->castShadow = true;

    return box;
}




