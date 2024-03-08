#pragma once
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"

namespace gui
{
class KeyboardManager : public State {
public:
    void update() {
        for (int i = 0; i < m_cur_state.size(); i++) {
            m_cur_state[i] = keyboard::isPressed(keyboard::Key(i));
            m_prev_state[i] = m_cur_state[i];
        }
    }
    bool isPressed(keyboard::Key key) {
        return m_cur_state[key];
    }
    bool isClicked(keyboard::Key key) {
        return m_cur_state[key] && !m_prev_state[key];
    }
private:
    std::vector<bool> m_cur_state;
    std::vector<bool> m_prev_state;
};
} // namespace gui

