#include <iostream>
#include "input/input.h"

using namespace Input;

InputController &InputController::getInstance() {
    static InputController singleton;
    return singleton;
}

void InputController::setControl(Input::Controls control, bool state) {
    this->controls_map[control] = state;
}

bool InputController::isKeyPressed(int key) {
    if (current_keyboard_event.code == key) return true;
    return false;
}

void InputController::setKeyPressed(KeyboardEvent key) {
    current_keyboard_event = key;
}

void InputController::printCurrentEvent() {
    if (current_keyboard_event.type != 0) {
        std::cout << "outer event!!" << std::endl;
        //std::cout << +current_keyboard_event.type << " - " << +current_keyboard_event.code << std::endl;
    }
}

bool InputController::isMoveTop() {
    return controls_map[Controls::MOVE_TOP];
}

bool InputController::isMoveRight() {
    return controls_map[Controls::MOVE_RIGHT];
}

bool InputController::isMoveDown() {
    return controls_map[Controls::MOVE_DOWN];
}

bool InputController::isMoveLeft() {
    return controls_map[Controls::MOVE_LEFT];
}

bool InputController::isAction() {
    return controls_map[Controls::ACTION];
}

bool InputController::isClose() {
    return controls_map[Controls::CLOSE];
}

bool InputController::isSecondary() {
    return controls_map[Controls::SECONDARY];
}
