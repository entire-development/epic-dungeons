#include <iostream>
#include "keyboard/keyboard.h"

using namespace Keyboard;

KeyboardController &KeyboardController::getInstance() {
    static KeyboardController singleton;
    if (singleton.key_states.empty()) singleton.key_states.resize(50);
    return singleton;
}

void KeyboardController::setKeyState(Key key, bool state) {
    if (key == Key::UNKNOWN) return;
    key_states[key] = state;
};

bool KeyboardController::isPressed(Key key) {
    if (key == Key::UNKNOWN) return false;
    return key_states[key];
}
