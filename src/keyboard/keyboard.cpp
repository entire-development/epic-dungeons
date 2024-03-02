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

const std::string keyToString(const Key &key) {
    // clang-format off
    switch (key) {
        case Key::KEY_1:        return "1";
        case Key::KEY_2:        return "2";
        case Key::KEY_3:        return "3";
        case Key::KEY_4:        return "4";
        case Key::KEY_5:        return "5";
        case Key::KEY_6:        return "6";
        case Key::KEY_7:        return "7";
        case Key::KEY_8:        return "8";
        case Key::KEY_9:        return "9";
        case Key::KEY_0:        return "0";
        case Key::KEY_A:        return "A";
        case Key::KEY_B:        return "B";
        case Key::KEY_C:        return "C";
        case Key::KEY_D:        return "D";
        case Key::KEY_E:        return "E";
        case Key::KEY_F:        return "F";
        case Key::KEY_G:        return "G";
        case Key::KEY_H:        return "H";
        case Key::KEY_I:        return "I";
        case Key::KEY_J:        return "J";
        case Key::KEY_K:        return "K";
        case Key::KEY_L:        return "L";
        case Key::KEY_M:        return "M";
        case Key::KEY_N:        return "N";
        case Key::KEY_O:        return "O";
        case Key::KEY_P:        return "P";
        case Key::KEY_Q:        return "Q";
        case Key::KEY_R:        return "R";
        case Key::KEY_S:        return "S";
        case Key::KEY_T:        return "T";
        case Key::KEY_U:        return "U";
        case Key::KEY_V:        return "V";
        case Key::KEY_W:        return "W";
        case Key::KEY_X:        return "X";
        case Key::KEY_Y:        return "Y";
        case Key::KEY_Z:        return "Z";
        case Key::KEY_UP:       return "UP";
        case Key::KEY_DOWN:     return "DOWN";
        case Key::KEY_LEFT:     return "LEFT";
        case Key::KEY_RIGHT:    return "RIGHT";
        case Key::KEY_SPACE:    return "SPACE";
        case Key::KEY_ENTER:    return "ENTER";
        case Key::KEY_ESCAPE:   return "ESCAPE";
        case Key::KEY_BACKSPACE:return "BACKSPACE";
        case Key::KEY_TAB:      return "TAB";
        case Key::KEY_SHIFT:    return "SHIFT";
        case Key::KEY_CTRL:     return "CTRL";
        case Key::KEY_ALT:      return "ALT";
        case Key::KEY_SUPER:    return "SUPER";
        default:                return "UNKNOWN";
    }
    // clang-format on
}

}   // namespace keyboard