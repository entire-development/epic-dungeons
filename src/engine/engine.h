#pragma once
#include "dungeon/dungeon.h"
#include "entity.h"
#include "heroes/gangster.h"
#include <memory>

namespace engine {
class Engine {
public:
    Engine() : m_dungeon(nullptr), m_party(nullptr) {
        m_party = std::make_shared<entities::Party>();
        m_party->addMember(std::make_shared<entities::Gangster>());
    }

    void bindDungeon(const std::shared_ptr<dungeon::Dungeon> &dungeon) {
        this->m_dungeon = dungeon;
    }

    std::shared_ptr<dungeon::Dungeon> getDungeon() {
        return m_dungeon;
    }

private:
    std::shared_ptr<dungeon::Dungeon> m_dungeon;
    std::shared_ptr<entities::Party> m_party;
};

class Battle {};
}   // namespace engine
