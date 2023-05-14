
#include <threepp/Canvas.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/scenes/Scene.hpp>
#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/lights/AmbientLight.hpp>
#include "spike/spikeVisualizer.hpp"


using namespace threepp;

int main() {

    std::string filePath = std::string(DATA_FOLDER) + "/topGameLogo.png";

    Canvas canvas{Canvas::Parameters()
                          .antialiasing(4)
                          .title("Top Game Spike Example")
                          .favicon(filePath)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();
    scene->background = 0x1a6c85;

    auto light = AmbientLight::create(0xffffff);
    scene->add(light);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 20;
    scene->add(camera);

    OrbitControls orbitControls(camera,canvas);

    auto vector3 = Vector3{0.0,0.0,0.0};
    auto spike = SpikeVisualizer::createSpike(vector3);
    spike->rotateX(-1.57); //-PI/2 ~ -1.57
    scene->add(spike);

    canvas.onWindowResize([&](WindowSize size) {
        renderer.setSize(size);
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
    });

    canvas.animate([&]() {
        renderer.render(scene, camera);
    });
}
