#include <threepp/Canvas.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/scenes/Scene.hpp>
#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/lights/AmbientLight.hpp>
#include "world/worldVisualizer.hpp"


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

    auto light = AmbientLight::create(0xffffff);

    scene->add(light);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 20;

    scene->add(camera);

    WorldVisualizer worldVisualizer{20,20};
    scene->add(worldVisualizer.flor);

    worldVisualizer.addBox({0.0,5.0,5.0},{2.5,2.5,2.5});
    worldVisualizer.addBox({5.0,0.0,5.0},{5.0,5.0,5.0});
    worldVisualizer.addBox({0.0,-5.0,5.0},{2.5,2.5,2.5});
    worldVisualizer.addBox({-5.0,0.0,5.0},{5.0,5.0,5.0});
    worldVisualizer.addBox({-5.0,-5.0,5.0},{2.5,2.5,2.5});
    worldVisualizer.addBox({5.0,-5.0,5.0},{2.5,2.5,2.5});
    worldVisualizer.addBox({-5.0,5.0,5.0},{2.5,2.5,2.5});
    worldVisualizer.addBox({5.0,5.0,5.0},{2.5,2.5,2.5});
    worldVisualizer.addBox({0.0,0.0,5.0},{2.5,2.5,2.5});

    for(const auto& element : worldVisualizer.boxes){
        scene->add(element);
    }

    canvas.onWindowResize([&](WindowSize size) {
        renderer.setSize(size);
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
    });

    canvas.animate([&]() {
        renderer.render(scene, camera);
    });
}
