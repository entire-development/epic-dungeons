#pragma once
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"

namespace gui {

class MainMenu : public State {
public:
    void enter(Controller *controller) {
        m_selected = 0;
        is_key_pressed = false;
        render(controller->m_renderer.get());
    }

    void update(Controller *controller) {
        bool pressed_up = keyboard::isPressed(keyboard::KEY_UP) || keyboard::isPressed(keyboard::KEY_W);
        bool pressed_down = keyboard::isPressed(keyboard::KEY_DOWN) || keyboard::isPressed(keyboard::KEY_S);
        bool pressed_enter = keyboard::isPressed(keyboard::KEY_ENTER);

        if (!(pressed_up || pressed_down || pressed_enter))
            is_key_pressed = false;

        if (is_key_pressed)
            return;

        if (pressed_up) {
            m_selected = (m_selected - 1 + m_options.size()) % m_options.size();
            is_key_pressed = true;
            render(controller->m_renderer.get());

        } else if (pressed_down) {
            m_selected = (m_selected + 1) % m_options.size();
            is_key_pressed = true;
            render(controller->m_renderer.get());
        } else if (pressed_enter) {
            switch (m_selected) {
                case 0:
                    controller->changeState(GUIState::kGame);
                    break;
                case 1:
                    controller->changeState(GUIState::kSettings);
                    break;
                case 2:
                    controller->changeState(GUIState::kExit);
                    break;
            }
        }
    };

    void exit(Controller *controller) {}

    void render(graphics::Renderer *renderer) {
        renderer->clear();
        for (int i = 0; i < m_options.size(); i++) {
            renderer->drawText(100, 100 + i * 50, m_options[i]);
            if (i == m_selected) {
                renderer->drawText(80, 100 + i * 50, ">");
            }
        }
        renderer->display();
    }

private:
    int m_selected = 0;
    std::vector<std::string> m_options = {"New Game", "Settings", "Exit"};
    bool is_key_pressed = false;
};

}   // namespace gui
