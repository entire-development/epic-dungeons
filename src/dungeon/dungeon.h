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
    // dungeon may be built only by DungeonMaker
    Dungeon() : m_rooms(), m_cells() {}

    std::vector<std::weak_ptr<Room>> getRooms() {
        return m_rooms;
    }

    std::weak_ptr<Cell> getCurrentCell() {
        return m_current_cell;
    }

    // find rooms which are connected with given room by corridor(cells)
    std::vector<std::weak_ptr<Room>> getRoomNeighbours(std::weak_ptr<Room> room);

    friend class IDungeonMaker;
    friend class MockDungeonMaker;

private:
    std::vector<std::weak_ptr<Room>> m_rooms;
    std::vector<std::shared_ptr<Cell>> m_cells;

    std::weak_ptr<Cell> m_current_cell;
};
}   // namespace dungeon
