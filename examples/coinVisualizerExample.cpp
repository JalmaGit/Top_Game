#include <threepp/Canvas.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/scenes/Scene.hpp>
#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/lights/AmbientLight.hpp>
#include "coin/coinVisualizer.hpp"


using namespace threepp;

int main() {

    std::string filePath = std::string(DATA_FOLDER) + "/topGameLogo.png";

    Canvas canvas{Canvas::Parameters()
                          .vsync(false)
                          .antialiasing(16)
                          .title("Top Game Example")
                          .favicon(filePath)};

    GLRenderer renderer{canvas};

    auto scene = Scene::create();
    scene->background = 0x1a6c85;

    auto light = AmbientLight::create(0xffffff);
    scene->add(light);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 20;

    OrbitControls orbitControls(camera,canvas);

    scene->add(camera);

    CoinVisualizer coinVisualizer;

    scene->add(coinVisualizer.coin);

    canvas.onWindowResize([&](WindowSize size) {
        renderer.setSize(size);
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
    });

    canvas.animate([&]() {
        renderer.render(scene, camera);
    });
}
