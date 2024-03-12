#pragma once
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"
#include "gui_controller/dialogue/dialogue.h"

namespace gui {

    class DialogueDemo : public State {
    public:
        dl::DialogueWindow dialogue_window = dl::DialogueWindow("Hello world", "456");

        void enter(Controller *controller) {
            render(controller->m_renderer.get());
        }

        void update(Controller *controller) {
            // render(controller->m_renderer.get());
        };

        void exit(Controller *controller) {}

        void render(graphics::Renderer *renderer) {
            renderer->clear();
            dialogue_window.drawQuote(renderer);
            renderer->display();
        }

    private:
        std::string m_text = "Hello world";
        bool is_key_pressed = false;
    };

}   // namespace gui
