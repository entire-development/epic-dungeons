#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <memory>

namespace gui {
namespace game {
class Event : public GameState {
    virtual void enter(GameMachine *gm) {
        auto cell = gm->m_engine.lock()->getDungeon()->getCurrentCell().lock();
        dungeon::CellType type = cell->getType();
        GUIGameState next_state = GUIGameState::kPostEvent;
        switch (type) {
            case dungeon::CellType::NOTHING:
                // if (!cell->isVisited())
                //     next_state = GUIGameState::kEmpty;
                break;
            case dungeon::CellType::FIGHT:
                if (!cell->isVisited())
                    next_state = GUIGameState::kBattle;
                break;
            default:
                break;
        }
        gm->changeState(next_state);
    }
};
}   // namespace game
}   // namespace gui