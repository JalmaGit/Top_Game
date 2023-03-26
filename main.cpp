#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

struct MyListener: KeyListener {

    int keyType{};

    bool button = false;

    void onKeyPressed(KeyEvent evt) override {
        if(evt.key==keyType){button=true;}
     //   std::cout << evt.key << std::endl;
    }

    void onKeyReleased(KeyEvent evt) override {
        if(evt.key==keyType){button=false;}
     //   std::cout << evt.key << std::endl;
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
    //Vector3 vector31{params.height,params.width,params.depth};
    //auto boxGeometry = BoxGeometry::create(vector31.x,vector31.y,vector31.z);
    auto boxGeometry = BoxGeometry::create(params);
    auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::skyblue;
    auto mesh = Mesh::create(boxGeometry,boxMaterial);
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

    PlaneGeometry::Params pictureSize{1739,1195};
    auto plane = createPlane(pictureSize);
    scene->add(plane);

    auto stlPlayerModel = createStlModel();
    scene->add(stlPlayerModel);

   // auto shadowBox = createStlModel();
   // scene->add(shadowBox);

    BoxGeometry::Params boxParams{25,25,25};
    auto box = createBox(boxParams);
    box->position.x=50;
    scene->add(box);

    Box3 box3;
    box3.setFromObject(*box);

    std::cout << box3 << "\n";

    Box3 box4;
    box4.setFromObject(*stlPlayerModel);

    std::cout << box4 << "\n";

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    auto lastPlayerPosition = stlPlayerModel->position;
  //  auto lastPlayerShadowPos = stlPlayerModel->position;
    auto lastCameraPos = camera->position;

    canvas.animate([&](float dt) {

        stlPlayerModel->geometry()->computeBoundingBox();
        box4.copy(*stlPlayerModel->geometry()->boundingBox).applyMatrix4(*stlPlayerModel->matrixWorld);

        std::cout << box3.intersectsBox(box4) << std::endl;

        if (!box3.intersectsBox(box4)) {
            lastPlayerPosition = stlPlayerModel->position;
            lastCameraPos = camera->position;
            if (keyW.buttonPressed()) {
            //    shadowBox->position.y++;
                camera->position.y++;
                stlPlayerModel->position.y++;
                stlPlayerModel->rotation.y = 0;
            }

            if (keyS.buttonPressed()) {
            //    shadowBox->position.y--;
                camera->position.y--;
                stlPlayerModel->position.y--;
                stlPlayerModel->rotation.y = math::PI;
            }
            if (keyD.buttonPressed()) {
            //    shadowBox->position.x++;
                camera->position.x++;
                stlPlayerModel->position.x++;
                stlPlayerModel->rotation.y = 3 * math::PI / 2;
            }
            if (keyA.buttonPressed()) {
            //    shadowBox->position.x--;
                camera->position.x--;
                stlPlayerModel->position.x--;
                stlPlayerModel->rotation.y = math::PI / 2;
            }
        }
        if (box3.intersectsBox(box4)){
            stlPlayerModel->position.copy(lastPlayerPosition);
            camera->position.copy(lastCameraPos);
        }

    /*    if (!box3.intersectsBox(box4)) {
            lastPlayerShadowPos = stlPlayerModel->position;
            if (keyW.buttonPressed()) {
                stlPlayerModel->position.y++;
            }
            if (keyS.buttonPressed()) {
                stlPlayerModel->position.y--;
            }
            if (keyD.buttonPressed()) {
                stlPlayerModel->position.x++;
            }
            if (keyA.buttonPressed()) {
                stlPlayerModel->position.x--;
            }

        }
        if (box3.intersectsBox(box4)){
            stlPlayerModel->position.copy(lastPlayerShadowPos);
        }
        //stlPlayerModel->position.copy(shadowBox->position);
        camera->position.copy(stlPlayerModel->position);
*/
        renderer.render(scene, camera);
    });
}

/*
        if (!box3.intersectsBox(box4)) {
            lastPlayerPosition = stlPlayerModel->position;
            lastCameraPos = camera->position;
            if (keyW.buttonPressed()) {
                shadowBox->position.y++;
                camera->position.y++;
                stlPlayerModel->position.y++;
                stlPlayerModel->rotation.y = 0;
            }

            if (keyS.buttonPressed()) {
                shadowBox->position.y--;
                camera->position.y--;
                stlPlayerModel->position.y--;
                stlPlayerModel->rotation.y = math::PI;
            }
            if (keyD.buttonPressed()) {
                shadowBox->position.x++;
                camera->position.x++;
                stlPlayerModel->position.x++;
                stlPlayerModel->rotation.y = 3 * math::PI / 2;
            }
            if (keyA.buttonPressed()) {
                shadowBox->position.x--;
                camera->position.x--;
                stlPlayerModel->position.x--;
                stlPlayerModel->rotation.y = math::PI / 2;
                }
        }
        if (box3.intersectsBox(box4)){
            stlPlayerModel->position.copy(lastPlayerPosition);
            camera->position.copy(lastCameraPos);
        }
    */

