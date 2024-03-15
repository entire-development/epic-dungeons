#pragma once
#include "dungeon/dungeon.h"
#include "engine/entity.h"
#include "gui_controller/game/game_machine.h"
#include "gui_controller/utils.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <gui_controller/keyboard_manager/keyboard_manager.h>
#include <memory>

namespace gui {
namespace game {
class Battle : public GameState {
public:
    Battle() : GameState() {
        m_enemy_party = std::make_shared<engine::entities::Party>();
        m_enemy_party->addMember(std::make_shared<engine::entities::Highwayman>());
        m_enemy_party->addMember(std::make_shared<engine::entities::Highwayman>());
        m_enemy_party->addMember(std::make_shared<engine::entities::Highwayman>());
    }

    virtual void enter(GameMachine *gm) {
        m_keyboard.reset();
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        render(gm);
    }

    virtual void update(GameMachine *gm) {
        m_keyboard.update();
        if (m_keyboard.isClicked(keyboard::Key::KEY_ENTER)) {
            gm->changeState(GUIGameState::kPostEvent);
        }
    }

    void render(GameMachine *gm) {
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        std::shared_ptr<dungeon::Cell> cell = gm->m_engine.lock()->getDungeon()->getCurrentCell().lock();
        std::shared_ptr<dungeon::Dungeon> dungeon = gm->m_engine.lock()->getDungeon();
        std::shared_ptr<engine::entities::Party> party = gm->m_engine.lock()->getParty();
        r->clear();
        utils::cellView(r, dungeon);
        for (size_t i = 0; i < party->getMembersCount(); i++) {
            utils::drawEntity(r, party->getMember(i), 3 - i, 0);
        }
        for (size_t i = 0; i < m_enemy_party->getMembersCount(); i++) {
            utils::drawEntity(r, m_enemy_party->getMember(i), 4 + i, 0);
        }

        r->display();
    }

private:
    std::shared_ptr<engine::entities::Party> m_enemy_party;
    KeyboardManager m_keyboard;
};

}   // namespace game
}   // namespace gui