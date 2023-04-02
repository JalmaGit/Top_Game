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
    auto box = Mesh::create(boxGeometry, boxMaterial);
    box->rotateX(math::PI / 2);
    box->position.z = params.height / 2;

    return box;
}

std::shared_ptr<Mesh> createPlane(float x, float y) {
    TextureLoader loader;

    auto planeGeometry = PlaneGeometry::create(x,y);
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
    auto stlModel = Mesh::create(stlGeometry, stlMaterial);
    stlModel->scale *= 0.2;
    stlModel->rotateX(math::PI / 2);

    return stlModel;
}
