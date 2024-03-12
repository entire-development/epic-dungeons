#pragma once
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"
#include "gui_controller/dialogue/dialogue.h"
#include "gui_controller/timed_count.h"

namespace gui {
    // TEMPORARY STATE. LATER WILL BE REFACTORED INTO DIALOGUE MANAGER CLASS.
    class DialogueDemo : public State {
    public:
        dl::DialogueWindow dialogue_window = dl::DialogueWindow();

        void enter(Controller *controller) {
            dialogue_window.changeQuote(quoteTexts[0], "123");
            render(controller->m_renderer.get());
            m_char_anim.init(0, quoteTexts[0].length() * 10, quoteTexts[0].length());
            m_char_anim.start();
        }

        void update(Controller *controller) {
            m_char_anim.update(controller->getDeltaTime());
            //render(controller->m_renderer.get());
        };

        void exit(Controller *controller) { }

        void render(graphics::Renderer *renderer) {
            renderer->clear();
            dialogue_window.drawQuote(renderer);
            m_char_anim.get();
            //std::cout << std::round(m_char_anim.get()) << std::endl;
            //dialogue_window.changeQuote(std::to_string(m_char_anim.get()), "123");
            //renderer->drawText(100, 100, std::to_string(m_char_anim.get()));
            renderer->display();
        }

    private:
        std::string m_text = "Hello world";
        bool is_key_pressed = false;
        TimedCount m_char_anim;
        std::vector<std::string> quoteTexts = {
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur."
        };
    };

}   // namespace gui
