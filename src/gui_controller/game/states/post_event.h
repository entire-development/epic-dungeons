#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <memory>

namespace gui {
namespace game {
class PostEvent : public GameState {
    virtual void enter(GameMachine *gm) {
        auto cell = gm->m_engine.lock()->getDungeon()->getCurrentCell().lock();
        cell->visit();
        gm->changeState(GUIGameState::kRoomSelection);
    }
};
}   // namespace game
}   // namespace gui