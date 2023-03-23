#include "threepp/threepp.hpp"

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters()};
    GLRenderer renderer(canvas);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(50, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 0.3;

    auto light = HemisphereLight::create();
    scene->add(light);

    TextureLoader loader;

    auto planeGeometry = PlaneGeometry::create();
    auto planeMaterial = SpriteMaterial::create();
    planeMaterial->map = loader.load("bin/data/textures/andenes.PNG");
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry,planeMaterial);
    plane->rotateX(math::degToRad(90));
    scene->add(plane);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

        renderer.render(scene, camera);
    });
}