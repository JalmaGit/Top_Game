#ifndef TOP_GAME_KEYINPUT_HPP
#define TOP_GAME_KEYINPUT_HPP

#include <threepp/input/KeyListener.hpp>
#include <threepp/math/Vector3.hpp>
#include <threepp/Canvas.hpp>


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


#endif //TOP_GAME_KEYINPUT_HPP
