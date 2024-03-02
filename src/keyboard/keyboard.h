#pragma once
#include <iostream>

namespace Keyboard {
    enum Key {
        UNKNOWN = -1,
        KEY_1 = 0, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
        KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,
        KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
        KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
        KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
        KEY_SPACE, KEY_ENTER, KEY_ESCAPE, KEY_BACKSPACE, KEY_TAB, KEY_SHIFT, KEY_CTRL, KEY_ALT, KEY_SUPER,
    };

    class KeyboardController {
        public:
            static KeyboardController& getInstance();

            void setKeyState(Key key, bool state);
            bool isPressed(Key key);

            KeyboardController() {};
            KeyboardController(KeyboardController const&) = delete;  // Prevent copy-construction
            KeyboardController& operator=(KeyboardController const&) = delete;  // Prevent assignment

        private:
            std::vector<bool> key_states = {};
    };
}

