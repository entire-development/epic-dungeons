#pragma once
#include <iostream>

namespace Input {
    struct KeyboardEvent {
        uint8_t code;
        uint8_t type;
    };

    class InputController {
        public:
            static InputController& getInstance();

            void setKeyboardEvent(KeyboardEvent event);
            void printCurrentEvent();
        private:
            KeyboardEvent current_keyboard_event;
            KeyboardEvent prev_keyboard_event;

            InputController() {};
            InputController(const InputController&);  // Prevent copy-construction
            InputController& operator=(const InputController&);  // Prevent assignment
    };
}
