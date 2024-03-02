#include <iostream>
#include "input/input.h"

using namespace Input;

InputController &InputController::getInstance() {
    static InputController singleton;
    if (singleton.key_states.empty()) singleton.key_states.resize(50);
    return singleton;
}

void InputController::setKeyState(Key key, bool state) {
    if (key == Key::UNKNOWN) return;
    key_states[key] = state;
}; // Read the upper line

bool InputController::isPressed(Key key) {
    if (key == Key::UNKNOWN) return false;
    return key_states[key];
};
