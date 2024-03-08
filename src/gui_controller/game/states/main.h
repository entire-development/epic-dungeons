#pragma once
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"

namespace gui {
namespace game {
class Main : public GameState {
    void enter(GameMachine *gm) override {
        graphics::Renderer *r = gm->m_renderer.lock().get();
        r->clear();
        render(r);
        r->display();
    }

    void render(graphics::Renderer *r) {
        r->drawRec({100, 100, 100, 100, sf::Color::Red});
        r->drawText(50, 300, "Press ESC to exit");
        graphics::Sprite sprite("test1.png");
        sprite.toSize(100, 100);
        r->draw(sprite, 0, 0);
    }
};
}   // namespace game
}   // namespace gui
