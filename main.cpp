#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

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

std::shared_ptr<Mesh> createPlane(const PlaneGeometry::Params& params) {
    TextureLoader loader;

    auto planeGeometry = PlaneGeometry::create(params);
    auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->map = loader.load("bin/data/textures/andenes.PNG");
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);

    return plane;
}

std::shared_ptr<Mesh> createStlModel() {
    STLLoader stlLoader;

    auto stlGeometry = stlLoader.load("bin/data/models/stl/mogus.stl");
    auto stlMaterial = MeshPhongMaterial::create();
    stlMaterial->flatShading = true;
    stlMaterial->color = Color::grey;
    auto mesh = Mesh::create(stlGeometry, stlMaterial);
    mesh->scale *= 0.2;
    mesh->rotateX(math::PI / 2);

    return mesh;
}

std::shared_ptr<Mesh> createBox(BoxGeometry::Params params){
    auto boxGemoetry = BoxGeometry::create(params);
    auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::skyblue;
    auto mesh = Mesh::create(boxGemoetry,boxMaterial);
    mesh->rotateX(math::PI/2);
    mesh->position.z=params.height/2;

    return mesh;
}

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 400);
    camera->position.z = 50;
    camera->position.y = -10;
    camera->rotation.x = math::PI/6;

    OrbitControls controls{camera, canvas};

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

    PlaneGeometry::Params pictureSize{1739,1195};
    auto plane = createPlane(pictureSize);
    scene->add(plane);

    auto stl = createStlModel();
    scene->add(stl);

    BoxGeometry::Params params1{25,25,25};
    auto box = createBox(params1);
    box->position.x=50;
    scene->add(box);


    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    canvas.animate([&](float dt) {
        if (keyW.buttonPressed()){
            camera->position.y++;
            stl->position.y++;
            stl->rotation.y=0;
        }
        if (keyS.buttonPressed()){
            camera->position.y--;
            stl->position.y--;
            stl->rotation.y=math::PI;
        }
        if (keyD.buttonPressed()){
            camera->position.x++;
            stl->position.x++;
            stl->rotation.y=3*math::PI/2;
        }
        if (keyA.buttonPressed()){
            camera->position.x--;
            stl->position.x--;
            stl->rotation.y=math::PI/2;
        }

        renderer.render(scene, camera);
    });
}