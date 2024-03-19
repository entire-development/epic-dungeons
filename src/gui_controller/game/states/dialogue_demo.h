#pragma once
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"
#include "gui_controller/dialogue/dialogue.h"
#include "gui_controller/timed_count.h"
#include "static_data/dialogue.h"
#include <iostream>

namespace gui {
namespace game {
// TEMPORARY STATE. LATER WILL BE REFACTORED INTO DIALOGUE MANAGER CLASS.
class DialogueDemo : public GameState {
    public:
    //dl::DialogueWindow dialogue_window = dl::DialogueWindow();
    dl::DialogueManager dialogue_manager = dl::DialogueManager();

    void enter(GameMachine *gm) {
        render(gm->m_renderer.lock());
    }

    void update(GameMachine *gm) {
        dialogue_manager.update(gm->getDeltaTime());
        if (keyboard::isPressed(cfg::CONTROLS_ACTION)) is_key_pressed = true;
        else {
            is_key_pressed = false;
            was_pressed = false;
        }
        if (is_key_pressed && !was_pressed) {
            if (dialogue_manager.isActive()) dialogue_manager.setEntryPoint(&quote_1, gm);
            else dialogue_manager.nextQuote(gm);
            was_pressed = true;
        }
        render(gm->m_renderer.lock());
    };

    void exit(Controller *controller) {}

    void render(std::shared_ptr<graphics::Renderer> renderer) {
        renderer->clear();
        dialogue_manager.draw(renderer);
        renderer->display();
    }

private:
    std::string m_text = "Hello world";
    bool is_key_pressed = false;
    bool was_pressed = false;
    TimedCount m_char_anim;
    mutable uint32_t current_quote = 0;
    std::vector<std::string> quoteTexts = {
            "Hello there. Sample text here, some amazing content. IDK what to write here.",
            "Quote 21!!!!!!!!!!!!!",
            "This. Is. Dot. Test.",
       };
};
}
}   // namespace gui
