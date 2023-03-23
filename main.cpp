#include "threepp/threepp.hpp"

#include <iostream>

using namespace threepp;

int main(){
    Canvas canvas(Canvas::Parameters().size(640,640));
    GLRenderer renderer(canvas);

    auto scene = Scene::create();
    auto camera = OrthographicCamera::create();

    OrbitControls controls{camera, canvas};

    const auto planeGeometry = PlaneGeometry::create(100, 100);
    const auto planeMaterial = MeshLambertMaterial::create();
    planeMaterial->color = Color::gray;
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);
    plane->rotateX(math::degToRad(90));
    plane->receiveShadow = true;
    scene->add(plane);


    canvas.onWindowResize([&](WindowSize size) {
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {
        renderer.render(scene,camera);
    });
}