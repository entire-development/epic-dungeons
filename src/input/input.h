#pragma once
#include <iostream>
#include <map>

namespace Input {
    struct KeyboardEvent {
        int code;
        int type;
    };

    enum Controls {
        MOVE_TOP,
        MOVE_RIGHT,
        MOVE_DOWN,
        MOVE_LEFT,
        ACTION,
        CLOSE,
        SECONDARY
    };

    class InputController {
        public:
            static InputController& getInstance();

            void setControl(Controls control, bool state);
            bool isKeyPressed(int key); // IDK how to implement it, SFML has complete key enum and I don't want to import it here ._.
            void setKeyPressed(KeyboardEvent key); // Read the upper line
            bool isMoveTop();
            bool isMoveRight();
            bool isMoveDown();
            bool isMoveLeft();
            bool isAction();
            bool isClose();
            bool isSecondary();
            void printCurrentEvent();

            InputController() {};
            InputController(InputController const&) = delete;  // Prevent copy-construction
            InputController& operator=(InputController const&) = delete;  // Prevent assignment
        private:
            KeyboardEvent current_keyboard_event;
            std::map<Controls, bool> controls_map = {
                    {Controls::MOVE_TOP, false},
                    {Controls::MOVE_RIGHT, false},
                    {Controls::MOVE_DOWN, false},
                    {Controls::MOVE_LEFT, false},
                    {Controls::ACTION, false},
                    {Controls::CLOSE, false},
                    {Controls::SECONDARY, false},
            };
    };
}
