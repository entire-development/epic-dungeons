#pragma once
#include "dungeon/dungeon.h"
#include <memory>

namespace engine {

class Engine {
public:
    Engine() : m_dungeon(nullptr) {}

    void bindDungeon(const std::shared_ptr<dungeon::Dungeon> &dungeon) {
        this->m_dungeon = dungeon;
    }

    std::shared_ptr<dungeon::Dungeon> getDungeon() {
        return m_dungeon;
    }

private:
    std::shared_ptr<dungeon::Dungeon> m_dungeon;
};
}   // namespace engine
