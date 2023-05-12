
#include "keyInput.hpp"

threepp::Vector3 KeyChecker::getKeyInput() {
    threepp::Vector3 nextMove = {0, 0, 0};
    if (keyW.buttonPressed()) {
        nextMove.y = 1;
    }

    if (keyS.buttonPressed()) {
        nextMove.y = -1;
    }

    if (keyD.buttonPressed()) {
        nextMove.x = 1;
    }

    if (keyA.buttonPressed()) {
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
