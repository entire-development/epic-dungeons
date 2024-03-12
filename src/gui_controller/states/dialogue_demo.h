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
            std::cout << "SDFSDDSF";
            std::cout << quoteTexts[0].length() << std::endl;
            m_char_anim.init(0, quoteTexts[0].length(), quoteTexts[0].length() * 30);
            m_char_anim.start();
            render(controller->m_renderer.get());
        }

        void update(Controller *controller) {
            m_char_anim.update(controller->getDeltaTime());
            dialogue_window.update(std::round(m_char_anim.get()));
            render(controller->m_renderer.get());
        };

        void exit(Controller *controller) { }

        void render(graphics::Renderer *renderer) {
            renderer->clear();
            dialogue_window.drawQuote(renderer);
            m_char_anim.get();
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
