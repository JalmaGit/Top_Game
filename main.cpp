#include <iostream>
#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"
#include "world.hpp"

using namespace threepp;

struct MyListener : KeyListener {

    int keyType{};

    bool button = false;

    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == keyType) { button = true; }
    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == keyType) { button = false; }
    }

    [[nodiscard]] bool buttonPressed() const {
        return button;
    }
};

int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 2000);
    camera->position.z = 50;
    camera->position.y = -10;
    camera->rotation.x = math::PI / 6;

    //Used to help with visualization
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

    //PlaneGeometry::Params pictureSize{1000, 500};
    //auto florPlane = createPlane(pictureSize);
    //scene->add(florPlane);

    auto stlPlayerModel = createStlModel();
    scene->add(stlPlayerModel);

    auto shadowBox = createStlModel();
    //shadowBox->material()->transparent = true;
    //shadowBox->material()->opacity = 0;
    shadowBox->visible= false;
    scene->add(shadowBox);

    BoxGeometry::Params boxParams{25, 25, 25};
    auto box = createBox(boxParams);
    box->position.x = 50;

    scene->add(box);

    Box3 box3;
    box3.setFromObject(*box);

    WorldGen worldGen{500,1000};

    scene->add(worldGen.worldFlor);


    //PlaneGeometry::Params pictureSize{1000, 500};
    //auto florPlane = createPlane(pictureSize);
    //scene->add(florPlane);

    Box3 worldHitBox[4]{};
    worldGen.getWorldEdge(worldHitBox);

    Box3 box3Shadow;
    box3Shadow.setFromObject(*shadowBox);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    auto lastPlayerShadowPos = shadowBox->position;
    bool hitBoxDetected{false};

    canvas.animate([&](float dt) {


        shadowBox->geometry()->computeBoundingBox();
        box3Shadow.copy(*shadowBox->geometry()->boundingBox).applyMatrix4(*shadowBox->matrixWorld);

        for (int i{}; i < std::size(worldHitBox); i++) {
            if (worldHitBox[i].intersectsBox(box3Shadow)) {
                hitBoxDetected = true;
                break;
            } else {
                hitBoxDetected = false;
            }
        }

        if (!hitBoxDetected) {
            if (box3.intersectsBox(box3Shadow)) {
                hitBoxDetected = true;
            } else {
                hitBoxDetected = false;
            }
        }

        if (!hitBoxDetected) {
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
        if (hitBoxDetected) {
            shadowBox->position.copy(lastPlayerShadowPos);
        }
        stlPlayerModel->position.copy(lastPlayerShadowPos);
        camera->position.x = lastPlayerShadowPos.x;
        camera->position.y = lastPlayerShadowPos.y - 10;

        renderer.render(scene, camera);
    });
}
