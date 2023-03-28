//
// Created by Jalma on 27.03.2023.
//
#include "geometryCreation.hpp"
#include <iostream>

using namespace threepp;

std::shared_ptr<Mesh> createBox(const BoxGeometry::Params params) {

    auto boxGeometry = BoxGeometry::create(params);
    auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::skyblue;
    auto mesh = Mesh::create(boxGeometry, boxMaterial);
    mesh->rotateX(math::PI / 2);
    mesh->position.z = params.height / 2;

    return mesh;
}

std::shared_ptr<Mesh> createPlane(const PlaneGeometry::Params &params) {
    TextureLoader loader;

    auto planeGeometry = PlaneGeometry::create(params);
    auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->map = loader.load("bin/data/textures/flor.png");
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);

    return plane;
}

std::shared_ptr<Mesh> createStlModel() {
    STLLoader stlLoader;

    auto stlGeometry = stlLoader.load("bin/data/models/stl/mogus.stl");
    auto stlMaterial = MeshPhongMaterial::create();
    stlMaterial->color = Color::grey;
    auto mesh = Mesh::create(stlGeometry, stlMaterial);
    mesh->scale *= 0.2;
    mesh->rotateX(math::PI / 2);

    return mesh;
}
