#pragma once
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"

namespace gui {
namespace game {
class Main : public GameState {
    bool is_pressed = false;

    void enter(GameMachine *gm) override {
        is_pressed = keyboard::isPressed(keyboard::KEY_ENTER);
        graphics::Renderer *r = gm->m_renderer.lock().get();
        r->clear();
        render(r);
        r->display();
    }

    void update(GameMachine *gm) override {
        if (!is_pressed && keyboard::isPressed(keyboard::KEY_ENTER)) {
            gm->changeState(GUIGameState::kRoomSelection);
            return;
        }
        is_pressed = keyboard::isPressed(keyboard::KEY_ENTER);
    }

    void render(graphics::Renderer *r) {
        r->drawText(50, 50, "Press ENTER to start the game");
        r->drawRec({100, 100, 100, 100, sf::Color::Red});
        r->drawText(50, 300, "Press ESC to exit");
    }
};
}   // namespace game
}   // namespace gui