#pragma once
#include <iostream>
#include <map>

namespace Input {
    struct KeyboardEvent {
        int code;
        int type;
    };

    enum Key {
        UNKNOWN = -1,
        KEY_1 = 0, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
        KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
        KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
        KEY_SPACE, KEY_ENTER, KEY_ESCAPE, KEY_BACKSPACE, KEY_TAB, KEY_SHIFT, KEY_CTRL, KEY_ALT, KEY_SUPER,
    };

//     struct Controls {
//        Keys MOVE_TOP = Keys::KEY_UP;
//        Keys MOVE_RIGHT = Keys::KEY_RIGHT;
//        Keys MOVE_DOWN = Keys::KEY_DOWN;
//        Keys MOVE_LEFT = Keys::KEY_LEFT;
//        Keys ACTION = Keys::KEY_Z;
//        Keys CLOSE = Keys::KEY_X;
//        Keys SECONDARY = Keys::KEY_C;
//    };

    class InputController {
        public:
            static InputController& getInstance();

            void setControl(Key control, bool state);
            void setKeyState(Key key, bool state); // Read the upper line

            bool isPressed(Key key);
            bool isMoveUp();
            bool isMoveRight();
            bool isMoveDown();
            bool isMoveLeft();
            bool isAction();
            bool isClose();
            bool isSecondary();

            InputController() {};
            InputController(InputController const&) = delete;  // Prevent copy-construction
            InputController& operator=(InputController const&) = delete;  // Prevent assignment

        private:
            std::vector<bool> key_states = {};
    };
}

