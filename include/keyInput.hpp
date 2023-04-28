//
// Created by Jalma on 11.04.2023.
//

#ifndef TOP_GAME_KEYINPUT_HPP
#define TOP_GAME_KEYINPUT_HPP

#include "threepp/threepp.hpp"
#include "iostream"

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

struct KeyChecker{

    auto setKeyInput(Canvas& canvas){
        keyW.keyType = W;
        canvas.addKeyListener(&keyW);

        keyA.keyType = A;
        canvas.addKeyListener(&keyA);

        keyS.keyType = S;
        canvas.addKeyListener(&keyS);

        keyD.keyType = D;
        canvas.addKeyListener(&keyD);
    }

    Vector2 getKeyInput(){
        Vector2 nextMove;
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

        return nextMove;
    }

private:


    int W{87};
    int A{65};
    int S{83};
    int D{68};

    MyListener keyW;
    MyListener keyA;
    MyListener keyS;
    MyListener keyD;

};

#endif //TOP_GAME_KEYINPUT_HPP
