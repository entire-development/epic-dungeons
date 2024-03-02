#include "keyboard.h"
#include <SFML/Window/Keyboard.hpp>

namespace keyboard {
const Key sfmlToKey(const sf::Keyboard::Key &key) {
    // clang-format off
  switch (key) {
    case sf::Keyboard::Num1:        return Key::KEY_1;
    case sf::Keyboard::Num2:        return Key::KEY_2;
    case sf::Keyboard::Num3:        return Key::KEY_3;
    case sf::Keyboard::Num4:        return Key::KEY_4;
    case sf::Keyboard::Num5:        return Key::KEY_5;
    case sf::Keyboard::Num6:        return Key::KEY_6;
    case sf::Keyboard::Num7:        return Key::KEY_7;
    case sf::Keyboard::Num8:        return Key::KEY_8;
    case sf::Keyboard::Num9:        return Key::KEY_9;
    case sf::Keyboard::Num0:        return Key::KEY_0;
    case sf::Keyboard::A:           return Key::KEY_A;
    case sf::Keyboard::B:           return Key::KEY_B;
    case sf::Keyboard::C:           return Key::KEY_C;
    case sf::Keyboard::D:           return Key::KEY_D;
    case sf::Keyboard::E:           return Key::KEY_E;
    case sf::Keyboard::F:           return Key::KEY_F;
    case sf::Keyboard::G:           return Key::KEY_G;
    case sf::Keyboard::H:           return Key::KEY_H;
    case sf::Keyboard::I:           return Key::KEY_I;
    case sf::Keyboard::J:           return Key::KEY_J;
    case sf::Keyboard::K:           return Key::KEY_K;
    case sf::Keyboard::L:           return Key::KEY_L;
    case sf::Keyboard::M:           return Key::KEY_M;
    case sf::Keyboard::N:           return Key::KEY_N;
    case sf::Keyboard::O:           return Key::KEY_O;
    case sf::Keyboard::P:           return Key::KEY_P;
    case sf::Keyboard::Q:           return Key::KEY_Q;
    case sf::Keyboard::R:           return Key::KEY_R;
    case sf::Keyboard::S:           return Key::KEY_S;
    case sf::Keyboard::T:           return Key::KEY_T;
    case sf::Keyboard::U:           return Key::KEY_U;
    case sf::Keyboard::V:           return Key::KEY_V;
    case sf::Keyboard::W:           return Key::KEY_W;
    case sf::Keyboard::X:           return Key::KEY_X;
    case sf::Keyboard::Y:           return Key::KEY_Y;
    case sf::Keyboard::Z:           return Key::KEY_Z;
    case sf::Keyboard::Up:          return Key::KEY_UP;
    case sf::Keyboard::Down:        return Key::KEY_DOWN;
    case sf::Keyboard::Left:        return Key::KEY_LEFT;
    case sf::Keyboard::Right:       return Key::KEY_RIGHT;
    case sf::Keyboard::Space:       return Key::KEY_SPACE;
    case sf::Keyboard::Return:      return Key::KEY_ENTER;
    case sf::Keyboard::Escape:      return Key::KEY_ESCAPE;
    case sf::Keyboard::BackSpace:   return Key::KEY_BACKSPACE;
    case sf::Keyboard::Tab:         return Key::KEY_TAB;
    case sf::Keyboard::LShift:      return Key::KEY_SHIFT;
    case sf::Keyboard::LControl:    return Key::KEY_CTRL;
    case sf::Keyboard::LAlt:        return Key::KEY_ALT;
    case sf::Keyboard::LSystem:     return Key::KEY_SUPER;
    default:                        return Key::UNKNOWN;
  }
    // clang-format on
}

void KeyboardController::setKeyState(const Key &key, bool state) {
    if (key == Key::UNKNOWN)
        return;
    key_states[key] = state;
};

const bool KeyboardController::isPressed(const Key &key) const {
    if (key == Key::UNKNOWN)
        return false;
    return key_states[key];
}

}   // namespace keyboard