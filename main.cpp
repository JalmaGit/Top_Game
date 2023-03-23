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

    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](auto &pos) {
        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });
    canvas.addMouseListener(&l);

    Raycaster raycaster;
    canvas.animate([&](float dt) {
        helper->visible = false;

        raycaster.setFromCamera(mouse, camera.get());
        auto intersects = raycaster.intersectObject(sprites.get(), true);
        if (!intersects.empty()) {
            auto &i = intersects.front();
            helper->position.copy(i.point);
            helper->visible = true;
        }

        renderer.render(scene, camera);
    });
}

/* using namespace threepp;

int main() {

    Canvas canvas(Canvas::Parameters().antialiasing(4).vsync(false));
    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::aqua);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create();

    auto planeGeo = PlaneGeometry::create();
    auto planeMesh = MeshBasicMaterial::create();
    planeMesh->side = DoubleSide;

    canvas.animate([&](float dt){

        renderer.render(scene, camera);

    });
} */