#include <threepp/Canvas.hpp>
#include <threepp/renderers/GLRenderer.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/scenes/Scene.hpp>
#include <threepp/cameras/PerspectiveCamera.hpp>
#include <threepp/lights/AmbientLight.hpp>
#include "world/worldVisualizer.hpp"


using namespace threepp;

int main() {

    Canvas canvas{Canvas::Parameters()
                          .vsync(false)
                          .antialiasing(16)
                          .title("Top Game Example")
                          .favicon("bin/data/topGameLogo.png")};

    GLRenderer renderer{canvas};

    auto scene = Scene::create();

    auto light = AmbientLight::create(0xffffff);

    scene->add(light);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 20;

    scene->add(camera);

    WorldVisualizer worldVisualizer{20,20};
    scene->add(worldVisualizer.flor);

    Vector3 boxPosition1{5.0,5.0,5.0};
    worldVisualizer.addBox(boxPosition1,{2.5,2.5,2.5});
    Vector3 boxPosition2{-5.0,5.0,5.0};
    worldVisualizer.addBox(boxPosition2,{2.5,2.5,2.5});
    Vector3 boxPosition3{5.0,-5.0,5.0};
    worldVisualizer.addBox(boxPosition3,{2.5,2.5,2.5});
    Vector3 boxPosition4{-5.0,-5.0,5.0};
    worldVisualizer.addBox(boxPosition4,{2.5,2.5,2.5});

    for(const auto& element : worldVisualizer.boxes){
        scene->add(element);
    }

    renderer.enableTextRendering();
    auto &textHandler = renderer.textHandle();

    canvas.onWindowResize([&](WindowSize size) {
        renderer.setSize(size);
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        textHandler.scale = size.getAspect();
    });

    canvas.animate([&]() {


        renderer.render(scene, camera);
    });
}
