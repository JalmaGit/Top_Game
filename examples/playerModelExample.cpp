
#include <threepp/Canvas.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/scenes/Scene.hpp>
#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/controls/OrbitControls.hpp>
#include <threepp/lights/PointLight.hpp>
#include <threepp/lights/AmbientLight.hpp>
#include "player/playerVisualizer.hpp"


using namespace threepp;

int main() {

    std::string filePath = std::string(DATA_FOLDER) + "/topGameLogo.png";

    Canvas canvas{Canvas::Parameters()
                          .vsync(false)
                          .antialiasing(16)
                          .title("Top Game Player Example")
                          .favicon(filePath)};

    GLRenderer renderer{canvas};

    auto scene = Scene::create();
    scene->background = 0xccdaf0;

    auto pointLight = PointLight::create(0xffffff);
    pointLight->intensity = 0.6f;
    pointLight->position.z = 20;
    pointLight->castShadow = true;
    scene->add(pointLight);

    auto ambientLight = AmbientLight::create(0xffffff);
    ambientLight->intensity = 0.4f;
    scene->add(ambientLight);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 20;

    OrbitControls orbitControls(camera, canvas);

    scene->add(camera);

    PlayerVisualizer playerVisualizer;

    scene->add(playerVisualizer.playerModel);

    canvas.onWindowResize([&](WindowSize size) {
        renderer.setSize(size);
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
    });

    canvas.animate([&]() {
        renderer.render(scene, camera);
    });
}