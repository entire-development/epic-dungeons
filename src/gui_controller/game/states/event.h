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
        GUIGameState next_state = GUIGameState::kRoomSelection;
        switch (type) {
            case dungeon::CellType::NOTHING:
                break;
            case dungeon::CellType::FIGHT:
                if (!cell->isVisited())
                    next_state = GUIGameState::kFight;
                break;
            case dungeon::CellType::SHOP:
                next_state = GUIGameState::kShop;
                break;
            default:
                break;
        }
        gm->changeState(next_state);
    }
};
}   // namespace game
}   // namespace gui