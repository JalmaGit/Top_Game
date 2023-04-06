#include <iostream>
#include "threepp/threepp.hpp"
#include "geometryCreation.hpp"
#include "world.hpp"
#include "player.hpp"

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

    Player player;
    std::shared_ptr<PerspectiveCamera> camera = player.getCameraCreation(canvas);
    scene->add(camera);
    scene->add(player.playerModel);
    scene->add(player.shadowBox);

    BoxGeometry::Params boxParams{25, 25, 25};
    auto box = createBox(boxParams,50);
    scene->add(box);
    Box3 box3;
    box3.setFromObject(*box);

    WorldGen worldGen{1000,500};
    scene->add(worldGen.worldFlor);

    Box3 box3Shadow;
    box3Shadow.setFromObject(*player.shadowBox);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    auto lastPlayerShadowPos = player.shadowBox->position;
    bool hitBoxDetected{false};

    canvas.animate([&](float dt) {


        player.shadowBox->geometry()->computeBoundingBox();
        box3Shadow.copy(*player.shadowBox->geometry()->boundingBox).applyMatrix4(*player.shadowBox->matrixWorld);

        for (int i{}; i < worldGen.worldWallHitBox.size(); i++) {
            if (worldGen.worldWallHitBox[i].intersectsBox(box3Shadow)) {
                hitBoxDetected = true;
                break;

            } else {
                hitBoxDetected = false;
            }
        }

        if (!hitBoxDetected) {
            if (box3.intersectsBox(box3Shadow)) {
                hitBoxDetected= true;
            } else {
                hitBoxDetected = false;
            }
        }

        if (!hitBoxDetected) {
            lastPlayerShadowPos = player.shadowBox->position;
            if (keyW.buttonPressed()) {
                player.shadowBox->position.y++;
                player.playerModel->rotation.y = 0;
            }
            if (keyS.buttonPressed()) {
                player.shadowBox->position.y--;
                player.playerModel->rotation.y = math::PI;
            }
            if (keyD.buttonPressed()) {
                player.shadowBox->position.x++;
                player.playerModel->rotation.y = 3 * math::PI / 2;
            }
            if (keyA.buttonPressed()) {
                player.shadowBox->position.x--;
                player.playerModel->rotation.y = math::PI / 2;
            }
        }
        if (hitBoxDetected) {
            player.shadowBox->position.copy(lastPlayerShadowPos);
        }
        player.playerModel->position.copy(lastPlayerShadowPos);
        camera->position.x = lastPlayerShadowPos.x;
        camera->position.y = lastPlayerShadowPos.y - 10;

        renderer.render(scene, camera);
    });
}
