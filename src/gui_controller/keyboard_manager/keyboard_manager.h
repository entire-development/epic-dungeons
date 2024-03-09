#pragma once
#include "keyboard/keyboard.h"
#include <vector>

namespace gui
{
class KeyboardManager {
public:
    void update() {
        for (int i = 0; i < m_cur_state.size(); i++) {
            m_prev_state[i] = m_cur_state[i];
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
    std::vector<bool> m_cur_state = std::vector<bool>(49, false);
    std::vector<bool> m_prev_state = std::vector<bool>(49, false);
};
} // namespace gui

