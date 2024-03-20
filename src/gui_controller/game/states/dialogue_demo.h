#pragma once
#include "gui_controller/controller.h"
#include "gui_controller/dialogue/dialogue.h"
#include "gui_controller/timed_count.h"
#include <iostream>

namespace gui {
namespace game {
// TEMPORARY STATE. LATER WILL BE REFACTORED INTO DIALOGUE MANAGER CLASS.
class DialogueDemo : public GameState {
    public:
    dl::DialogueManager dialogue_manager = dl::DialogueManager();

    void enter(GameMachine *gm) {
        m_keyboard_manager.reset();
        render(gm->m_renderer.lock());
    }

    void update(GameMachine *gm) {
        m_keyboard_manager.update();
        dialogue_manager.handleKeyboard(m_keyboard_manager, gm);
        render(gm->m_renderer.lock());
    };

    void exit(Controller *controller) {}

    void render(std::shared_ptr<graphics::Renderer> renderer) {
        renderer->clear();
        dialogue_manager.draw(renderer);
        renderer->display();
    }

private:
    KeyboardManager m_keyboard_manager;
};
}
}   // namespace gui
