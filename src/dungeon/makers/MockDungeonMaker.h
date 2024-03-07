#pragma once
#include "dungeon/dungeon.h"
#include <memory>

namespace dungeon {
class MockDungeonMaker : public IDungeonMaker {
public:
    void build() final;
    std::shared_ptr<Dungeon> getDungeon() final;

private:
    std::shared_ptr<Dungeon> dungeon;
};
}   // namespace dungeon
