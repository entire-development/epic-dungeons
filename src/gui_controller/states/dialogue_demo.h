#pragma once
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"
#include "gui_controller/dialogue/dialogue.h"
#include "gui_controller/timed_count.h"
#include <cmath>

dl::script::QuoteNode quote_3 = {
        .content = "Quote 3!",
        .sprite = "123",
        .next = nullptr
};

dl::script::QuoteNode quote_2 = {
        .content = "Quote 2!",
        .sprite = "123",
        .next = &quote_3
};

dl::script::QuoteNode quote_1 = {
        .content = "Quote 1!",
        .sprite = "123",
        .next = &quote_2
};

namespace gui {
    // TEMPORARY STATE. LATER WILL BE REFACTORED INTO DIALOGUE MANAGER CLASS.
    class DialogueDemo : public State {
    public:
        //dl::DialogueWindow dialogue_window = dl::DialogueWindow();
        dl::DialogueManager dialogue_manager = dl::DialogueManager();

        void enter(Controller *controller) {
//            dialogue_window.changeQuote(quoteTexts[0], "123");
//            size_t str_len = dl::preprocessString(quoteTexts[0]).length();
//            m_char_anim.init(0, str_len, str_len * cfg::DIALOGUE_FONT_SPEED);
//            m_char_anim.start();
//            render(controller->m_renderer.get());
        }

        void update(Controller *controller) {
            dialogue_manager.update(controller->getDeltaTime(), controller->m_renderer.get());
//            m_char_anim.update(controller->getDeltaTime());
//            dialogue_window.update(std::round(m_char_anim.get()));
//
//            bool action = keyboard::isPressed(cfg::CONTROLS_ACTION);
//
//            if (action && current_quote < quoteTexts.size() - 1 && m_char_anim.isEnded()) {
//                current_quote++;
//                dialogue_window.changeQuote(quoteTexts[current_quote], "123");
//                size_t str_len = dl::preprocessString(quoteTexts[current_quote]).length();
//                m_char_anim.init(0, str_len, str_len * cfg::DIALOGUE_FONT_SPEED);
//                m_char_anim.start();
//            }
//
//            render(controller->m_renderer.get());
        };

        void exit(Controller *controller) { }

        void render(graphics::Renderer *renderer) {
//            renderer->clear();
//            dialogue_window.drawQuote(renderer);
//            //renderer->draw(graphics::Text(std::to_string(m_char_anim.get())), 100, 100);
//            renderer->display();
        }

    private:
        std::string m_text = "Hello world";
        bool is_key_pressed = false;
        TimedCount m_char_anim;
        mutable uint32_t current_quote = 0;
        std::vector<std::string> quoteTexts = {
                "[color=#fa8072][size=18]HIHIHIH[/size][/color]. HHUHUHU Hahahahah",
                "Zdarova [color=#ff0000]chelik, kak tvoi dela???[/color]",
                "Hello there. Sample text here, some amazing content. IDK what to write here.",
                "Quote 21!!!!!!!!!!!!!",
                "This. Is. Dot. Test.",
        };
    };
}   // namespace gui
