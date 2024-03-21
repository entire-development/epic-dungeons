#pragma once
#include "keyboard/keyboard.h"
#include <vector>

namespace gui {
class KeyboardManager {
public:
    KeyboardManager() : m_cur_state(49, false), m_prev_state(49, false) {}

    void update() {
        for (int i = 0; i < m_cur_state.size(); i++) {
            m_prev_state[i] = m_cur_state[i];
            m_cur_state[i] = keyboard::isPressed(keyboard::Key(i));
        }
    }

    void reset() {
        for (int i = 0; i < m_cur_state.size(); i++) {
            m_prev_state[i] = keyboard::isPressed(keyboard::Key(i));
            m_cur_state[i] = keyboard::isPressed(keyboard::Key(i));
        }
    }

    bool isPressed(const keyboard::Key &key) const {
        return m_cur_state[key];
    }

    bool isClicked(const keyboard::Key &key) const {
        return m_cur_state[key] && !m_prev_state[key];
    }

private:
    std::vector<uint8_t> m_cur_state;
    std::vector<uint8_t> m_prev_state;
};
}   // namespace gui
