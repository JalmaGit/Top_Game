#include <iostream>
#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"

using namespace threepp;

struct MyListener : KeyListener {

    int keyType{};

    bool button = false;

    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == keyType) { button = true; }
        //   std::cout << evt.key << std::endl;
    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == keyType) { button = false; }
        //   std::cout << evt.key << std::endl;
    }

    bool buttonPressed() {
        return button;
    }
};


auto createUpperWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params topBoxParams{params.width, params.height, 100};
    auto upperBox = createBox(topBoxParams);
    upperBox->position.y = params.depth / 2 + topBoxParams.depth / 2;
    Box3 upperHitBox;
    return upperHitBox.setFromObject(*upperBox);
}

auto createLowerWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params downBoxParams{params.width, params.height, 100};
    auto lowerBox = createBox(downBoxParams);
    lowerBox->position.y = -params.depth / 2 - downBoxParams.depth / 2;
    Box3 lowerHitBox;
    return lowerHitBox.setFromObject(*lowerBox);
}

auto createRightWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params rightBoxParams{100, params.height, params.depth};
    auto rightBox = createBox(rightBoxParams);
    rightBox->position.x = params.width / 2 + rightBoxParams.width / 2;
    Box3 rightHitBox;
    return rightHitBox.setFromObject(*rightBox);
}

auto createLeftWorldEdge(const BoxGeometry::Params params) {
    BoxGeometry::Params leftBoxParams{100, params.height, params.depth};
    auto leftBox = createBox(leftBoxParams);
    leftBox->position.x = -params.width / 2 - leftBoxParams.width / 2;
    Box3 leftHitBox;
    return leftHitBox.setFromObject(*leftBox);
}


int main() {

    Canvas canvas{Canvas::Parameters().antialiasing(4)};
    GLRenderer renderer{canvas};

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 400);
    camera->position.z = 50;
    camera->position.y = -10;
    camera->rotation.x = math::PI / 6;

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

    PlaneGeometry::Params pictureSize{1739, 1195};
    auto plane = createPlane(pictureSize);
    scene->add(plane);

    auto stlPlayerModel = createStlModel();
    scene->add(stlPlayerModel);

    auto shadowBox = createStlModel();
    shadowBox->material()->transparent = true;
    shadowBox->material()->opacity = 0.5;
    scene->add(shadowBox);

    BoxGeometry::Params boxParams{25, 25, 25};
    auto box = createBox(boxParams);
    box->position.x = 50;
    scene->add(box);

    BoxGeometry::Params edgeBox{pictureSize.width, 30, pictureSize.height};

    Box3 box3;
    box3.setFromObject(*box);

    Box3 worldHitBox[4]{createUpperWorldEdge(edgeBox), createLowerWorldEdge(edgeBox), createRightWorldEdge(edgeBox), createLeftWorldEdge(edgeBox)};

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
    bool crash{false};

    canvas.animate([&](float dt) {


        shadowBox->geometry()->computeBoundingBox();
        box3Shadow.copy(*shadowBox->geometry()->boundingBox).applyMatrix4(*shadowBox->matrixWorld);

        for (int i{}; i < std::size(worldHitBox); i++){
            if(worldHitBox[i].intersectsBox(box3Shadow)){
                crash = true;
                break;
            } else {
                crash = false;
            }
        }
        if(!crash) {
            if (box3.intersectsBox(box3Shadow)) {
                crash = true;
            } else {
                crash = false;
            }
        }

        if (!crash) {
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
        if (crash) {
            shadowBox->position.copy(lastPlayerShadowPos);
        }
        stlPlayerModel->position.copy(lastPlayerShadowPos);
        camera->position.x = lastPlayerShadowPos.x;
        camera->position.y = lastPlayerShadowPos.y - 10;

        renderer.render(scene, camera);
    });
}
