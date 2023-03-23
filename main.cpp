#include "threepp/threepp.hpp"

using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(8)};
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aliceblue);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 0.2;

    TextureLoader loader;
    auto material = SpriteMaterial::create();
    material->map = loader.load("bin/data/textures/andenes.PNG");
    material->map->offset.set(0.5, 0.5);

    auto sprites = Group::create();
    auto sprite = Sprite::create(material);
    sprite->position.x = static_cast<float>(0);
    sprite->position.y = static_cast<float>(0);
    sprites->add(sprite);

    scene->add(sprites);

    auto helper = Mesh::create(SphereGeometry::create(0.1));
    scene->add(helper);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {
        helper->visible = false;

        renderer.render(scene, camera);
    });
}