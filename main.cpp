#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

struct GameBackground{
    float width{};
    float height{};
};

struct MyListener: KeyListener {

    int keyType{};

    bool button = false;

    void onKeyPressed(KeyEvent evt) override {
        if(evt.key==keyType){button=true;}
        std::cout << evt.key << std::endl;
    }

    void onKeyReleased(KeyEvent evt) override {
        if(evt.key==keyType){button=false;}
        std::cout << evt.key << std::endl;
    }

    bool buttonPressed(){
        return button;
    }
};

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 400);
    camera->position.z = 50;

    //OrbitControls controls{camera, canvas};

    MyListener keyW;
    keyW.keyType = 87;
    canvas.addKeyListener(&keyW);

    MyListener keyA;
    keyA.keyType = 65;
    canvas.addKeyListener(&keyA);

    MyListener keyS;
    keyS.keyType = 83;
    canvas.addKeyListener(&keyS);

    MyListener keyD;
    keyD.keyType = 68;
    canvas.addKeyListener(&keyD);

    auto light = HemisphereLight::create(Color::aliceblue, Color::grey);
    scene->add(light);

    TextureLoader loader;

    GameBackground pictureSize{1739,1195};

    auto planeGeometry = PlaneGeometry::create(pictureSize.width, pictureSize.height);
    auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->map = loader.load("bin/data/textures/andenes.PNG");
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);
    plane->position.y = 0;
    scene->add(plane);

    STLLoader stlLoader;
    auto stlGeometry = stlLoader.load("bin/data/models/stl/Amog_US.stl");
    auto stlMaterial = MeshPhongMaterial::create();
    stlMaterial->flatShading = true;
    stlMaterial->color = Color::grey;
    auto mesh = Mesh::create(stlGeometry,stlMaterial);
    mesh->scale *= 0.3;
    mesh->rotateX(math::PI / 2);
    mesh->position.x=10;
    scene->add(mesh);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {
        if (keyW.buttonPressed()){
            camera->position.y++;
        }
        if (keyS.buttonPressed()){
            camera->position.y--;
        }
        if (keyD.buttonPressed()){
            camera->position.x++;
        }
        if (keyA.buttonPressed()){
            camera->position.x--;
        }

        renderer.render(scene, camera);
    });
}