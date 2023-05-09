//
// Created by Jalma on 11.04.2023.
//

#ifndef TOP_GAME_KEYINPUT_HPP
#define TOP_GAME_KEYINPUT_HPP

#include "threepp/input/KeyListener.hpp"
#include "threepp/math/Vector2.hpp"


struct MyListener : threepp::KeyListener {

    int keyType{};

    bool button = false;

    void onKeyPressed(threepp::KeyEvent evt) override {
        if (evt.key == keyType) { button = true; }
    }

    void onKeyReleased(threepp::KeyEvent evt) override {
        if (evt.key == keyType) { button = false; }
    }

    [[nodiscard]] bool buttonPressed() const {
        return button;
    }
};

struct KeyChecker {

    void setKeyInput(threepp::Canvas &canvas);

    threepp::Vector3 getKeyInput();

private:
    int W{87};
    int A{65};
    int S{83};
    int D{68};
    int R{82};

    MyListener keyW;
    MyListener keyA;
    MyListener keyS;
    MyListener keyD;
    MyListener keyR;

};

threepp::Vector3 KeyChecker::getKeyInput() {
    threepp::Vector3 nextMove = {0, 0, 0};
    if (keyW.buttonPressed()) {
        nextMove.y = 1;
    }
    if (keyS.buttonPressed()) {
        nextMove.y = -1;
    }
    if (keyA.buttonPressed()) {
        nextMove.x = 1;
    }
    if (keyD.buttonPressed()) {
        nextMove.x = -1;
    }
    if (keyR.buttonPressed()) {
        nextMove.z = 1;
    }

    return nextMove;
}

void KeyChecker::setKeyInput(threepp::Canvas &canvas) {
    keyW.keyType = W;
    canvas.addKeyListener(&keyW);

    keyA.keyType = A;
    canvas.addKeyListener(&keyA);

    keyS.keyType = S;
    canvas.addKeyListener(&keyS);

    keyD.keyType = D;
    canvas.addKeyListener(&keyD);

    keyR.keyType = R;
    canvas.addKeyListener(&keyR);
}

#endif //TOP_GAME_KEYINPUT_HPP
