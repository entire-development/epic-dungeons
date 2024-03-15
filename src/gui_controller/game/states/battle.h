#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/game/game_machine.h"
#include "gui_controller/utils.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <memory>

namespace gui {
namespace game {
class Battle : public GameState {
    virtual void enter(GameMachine *gm) {
        is_pressed = true;
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
    }

    virtual void update(GameMachine *gm) {
        if (!is_pressed && keyboard::isPressed(keyboard::KEY_ENTER)) {
            gm->changeState(GUIGameState::kPostEvent);
        }
        is_pressed = keyboard::isPressed(keyboard::KEY_ENTER);
    }

    bool is_pressed;

    void render(GameMachine *gm) {
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        std::shared_ptr<dungeon::Cell> cell = gm->m_engine.lock()->getDungeon()->getCurrentCell().lock();
        std::shared_ptr<dungeon::Dungeon> dungeon = gm->m_engine.lock()->getDungeon();
        r->clear();
        utils::cellView(r, dungeon);
    }
};
}   // namespace game
}   // namespace gui