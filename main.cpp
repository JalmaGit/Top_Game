#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

struct GameBackgroundSize{
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

    GameBackgroundSize pictureSize{1739,1195};
    PlaneGeometry::Params params{pictureSize.width,pictureSize.height};
    auto plane = createPlane(params);
    scene->add(plane);

    auto stlPlayerModel = createStlModel();
    scene->add(stlPlayerModel);

    auto shadowBox = createStlModel();
    shadowBox->material()->transparent=true;
    shadowBox->material()->opacity=0;
    scene->add(shadowBox);

    BoxGeometry::Params params1{50,50,50};
    auto box = createBox(params1);
    box->rotateX(math::PI/2);
    box->position.x=50;
    scene->add(box);

    Box3 box3;
    box3.setFromObject(*box);

    std::cout << box3 << "\n";

    Box3 box3Shadow;
    box3Shadow.setFromObject(*shadowBox);

    std::cout << box3Shadow << "\n";

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    auto lastPlayerShadowPos = shadowBox->position;
    int crash{};

    canvas.animate([&](float dt) {

        shadowBox->geometry()->computeBoundingBox();
        box3Shadow.copy(*shadowBox->geometry()->boundingBox).applyMatrix4(*shadowBox->matrixWorld);

        if (!box3.intersectsBox(box3Shadow)) {
            lastPlayerShadowPos = shadowBox->position;
            if (keyW.buttonPressed()) {
                shadowBox->position.y++;
                stlPlayerModel->rotation.y = 0;
            }
            if (keyS.buttonPressed()) {
                shadowBox->position.y--;
                stlPlayerModel->rotation.y = math::PI;
            }
            if (keyD.buttonPressed()) {
                shadowBox->position.x++;
                stlPlayerModel->rotation.y = 3 * math::PI / 2;
            }
            if (keyA.buttonPressed()) {
                shadowBox->position.x--;
                stlPlayerModel->rotation.y = math::PI / 2;
            }
        }
        if (box3.intersectsBox(box3Shadow)){
            shadowBox->position.copy(lastPlayerShadowPos);
            crash = 0;
        }
        stlPlayerModel->position.copy(lastPlayerShadowPos);
        camera->position.x = lastPlayerShadowPos.x;
        camera->position.y = lastPlayerShadowPos.y-10;

        renderer.render(scene, camera);
    });
}