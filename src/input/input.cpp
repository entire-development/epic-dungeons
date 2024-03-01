#include <iostream>
#include "input/input.h"

using namespace Input;

InputController &InputController::getInstance() {
    static InputController singleton;
    return singleton;
}

void InputController::setKeyboardEvent(KeyboardEvent event) {
    this->prev_keyboard_event = current_keyboard_event;
    this->current_keyboard_event = event;
}

void InputController::printCurrentEvent() {
    std::cout << current_keyboard_event.type << " - " << current_keyboard_event.code << std::endl;
}
