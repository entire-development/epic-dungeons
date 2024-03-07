#pragma once
#include "cell/cell.h"
#include <memory>
#include <vector>

namespace dungeon {
class Dungeon;
class IDungeonMaker;

class IDungeonMaker {
public:
    virtual void build() = 0;
    virtual std::shared_ptr<Dungeon> getDungeon() = 0;
};

class Dungeon {
public:
    std::vector<std::weak_ptr<Room>> getRooms();
    std::shared_ptr<Cell> getCurrentCell();

    // find rooms which are connected with given room by corridor(cells)
    std::vector<Room> getRoomNeighbours(std::weak_ptr<Room> room);

    friend class IDungeonMaker;
    friend class MockDungeonMaker;

private:
    // dungeon may be built only by DungeonMaker
    Dungeon() = default;

    std::vector<std::weak_ptr<Room>> m_rooms;
    std::vector<std::shared_ptr<Cell>> m_cells;

    std::shared_ptr<Cell> m_current_cell = nullptr;
};
}   // namespace dungeon
