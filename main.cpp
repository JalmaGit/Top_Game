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

<<<<<<< Updated upstream
=======
void checkIntersect(){

}


>>>>>>> Stashed changes
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

    auto stl = createStlModel();
    scene->add(stl);

<<<<<<< Updated upstream
    BoxGeometry::Params params1{50,50,50};
    auto box = createBox(params1);
    box->rotateX(math::PI/2);
    box->position.x=50;
    scene->add(box);

=======
    auto shadowBox = createStlModel();
    shadowBox->material()->transparent=true;
    shadowBox->material()->opacity=0.3;
    scene->add(shadowBox);


    BoxGeometry::Params boxParams{25,25,25};
    auto box = createBox(boxParams);
    box->position.x=50;
    scene->add(box);

    Box3 box3;
    box3.setFromObject(*box);

    std::cout << box3 << "\n";

    Box3 box3Shadow;
    box3Shadow.setFromObject(*shadowBox);

    std::cout << box3Shadow << "\n";

>>>>>>> Stashed changes
    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

<<<<<<< Updated upstream
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

=======
    auto lastPlayerPosition = stlPlayerModel->position;
    auto lastPlayerShadowPos = shadowBox->position;
    auto lastCameraPos = camera->position;
    bool crash{true};

    canvas.animate([&](float dt) {

        shadowBox->geometry()->computeBoundingBox();
        box3Shadow.copy(*shadowBox->geometry()->boundingBox).applyMatrix4(*shadowBox->matrixWorld);

        std::cout << box3.intersectsBox(box3Shadow) << std::endl;

        if (!box3.intersectsBox(box3Shadow)) {
            lastPlayerShadowPos = shadowBox->position;
            if (keyW.buttonPressed()) {
                shadowBox->position.y++;
            }
            if (keyS.buttonPressed()) {
                shadowBox->position.y--;
            }
            if (keyD.buttonPressed()) {
                shadowBox->position.x++;
            }
            if (keyA.buttonPressed()) {
                shadowBox->position.x--;
            }
        }
        if (box3.intersectsBox(box3Shadow)){
            shadowBox->position.copy(lastPlayerShadowPos);
        }
        stlPlayerModel->position.copy(shadowBox->position);


/*
        if (shadowBox->position != lastPlayerShadowPos) {
            if (keyW.buttonPressed()) {
                camera->position.y++;
                stlPlayerModel->position.y++;
                stlPlayerModel->rotation.y = 0;
            }

            if (keyS.buttonPressed()) {
                camera->position.y--;
                stlPlayerModel->position.y--;
                stlPlayerModel->rotation.y = math::PI;
            }
            if (keyD.buttonPressed()) {
                camera->position.x++;
                stlPlayerModel->position.x++;
                stlPlayerModel->rotation.y = 3 * math::PI / 2;
            }
            if (keyA.buttonPressed()) {
                camera->position.x--;
                stlPlayerModel->position.x--;
                stlPlayerModel->rotation.y = math::PI / 2;
            }
        }
*/
>>>>>>> Stashed changes
        renderer.render(scene, camera);
    });
}