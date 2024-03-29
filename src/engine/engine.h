#pragma once
#include "dungeon/dungeon.h"
#include "entity.h"
#include "heroes/bounty_hunter.h"
#include "heroes/crusader.h"
#include "heroes/highwayman.h"
#include <memory>

namespace engine {
class Engine {
public:
    Engine() : m_dungeon(nullptr), m_party(nullptr) {
        m_party = std::make_shared<entities::Party>();
        m_party->addMember(std::make_shared<entities::Highwayman>());
        m_party->addMember(std::make_shared<entities::Crusader>());
        m_party->addMember(std::make_shared<entities::BountyHunter>());
    }

    void bindDungeon(const std::shared_ptr<dungeon::Dungeon> &dungeon) {
        this->m_dungeon = dungeon;
    }

    std::shared_ptr<dungeon::Dungeon> getDungeon() const {
        return m_dungeon;
    }

    std::shared_ptr<entities::Party> getParty() const {
        return m_party;
    }

private:
    std::shared_ptr<dungeon::Dungeon> m_dungeon;
    std::shared_ptr<entities::Party> m_party;
};

class Battle {};
}   // namespace engine
