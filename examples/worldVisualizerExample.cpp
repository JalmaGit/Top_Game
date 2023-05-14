
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
                          .antialiasing(4)
                          .title("World Visualizer Example")
                          .favicon(filePath)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();

    auto light = AmbientLight::create(0xffffff);
    scene->add(light);

    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 20;

    scene->add(camera);

    //Building a simple world to showcase it

    WorldVisualizer worldVisualizer{20,20};
    scene->add(worldVisualizer.flor);

    Vector3 position = {0.0,5.0,5.0} , size = {2.5,2.5,2.5};
    worldVisualizer.addBox(position,size);

    position ={0.0,-5.0,5.0};
    worldVisualizer.addBox(position,size);

    position ={-5.0,-5.0,5.0};
    worldVisualizer.addBox(position,size);

    position ={5.0,-5.0,5.0};
    worldVisualizer.addBox(position,size);

    position ={5.0,-5.0,5.0};
    worldVisualizer.addBox(position,size);

    position ={-5.0,5.0,5.0};
    worldVisualizer.addBox(position,size);

    position ={5.0,5.0,5.0};
    worldVisualizer.addBox(position,size);

    position ={0.0,0.0,5.0};
    worldVisualizer.addBox(position,size);

    size = {5.0,5.0,5.0};

    position = {5.0,0.0,5.0};
    worldVisualizer.addBox(position,size);

    position = {-5.0,0.0,5.0};
    worldVisualizer.addBox(position,size);

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
