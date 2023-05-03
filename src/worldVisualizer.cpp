//
// Created by Jalma on 01/05/2023.
//
#include "worldVisualizer.hpp"
#include "threepp/loaders/TextureLoader.hpp"
#include "threepp/geometries/PlaneGeometry.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"
#include "threepp/geometries/BoxGeometry.hpp"

using namespace threepp;

std::shared_ptr<Mesh> WorldVisualizer::addPlane(float width, float length) {
    TextureLoader loader;

    auto planeGeometry = PlaneGeometry::create(width,length);
    auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->map = loader.load("bin/data/textures/flor.png");
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);

    return plane;
}

std::shared_ptr<Mesh> WorldVisualizer::createBox(Vector3 boxPosition, Vector3 boxSize) {

    auto boxGeometry = BoxGeometry::create(boxSize.x,boxSize.y,boxSize.z);
    auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::skyblue;
    auto box = Mesh::create(boxGeometry, boxMaterial);
    box->rotateX(math::PI / 2);
    box->position = boxPosition;

    return box;
}
