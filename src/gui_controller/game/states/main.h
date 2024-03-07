#pragma once
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"

namespace gui {
namespace game {
class Main : public GameState {
    bool is_presssed = false;

    void enter(GameMachine *gm) override {
        is_presssed = keyboard::isPressed(keyboard::KEY_ENTER);
        renderer::SFMLRenderer *r = gm->m_renderer.lock().get();
        r->clear();
        render(r);
        r->display();
    }

    void update(GameMachine *gm) override {
        if (!is_presssed && keyboard::isPressed(keyboard::KEY_ENTER)) {
            gm->changeState(GUIGameState::kRoomSelection);
            return;
        }
        is_presssed = keyboard::isPressed(keyboard::KEY_ENTER);
    }

    void render(renderer::SFMLRenderer *r) {
        r->drawText(50, 50, "Press ENTER to start");
        r->drawRec({100, 100, 100, 100, sf::Color::Red});
        r->drawText(50, 300, "Press ESC to exit");
    }
};
}   // namespace game
}   // namespace gui