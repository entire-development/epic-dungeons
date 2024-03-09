#pragma once
#include "cell/cell.h"
#include <memory>
#include <utility>
#include <vector>

namespace dungeon {
class Dungeon;
class IDungeonMaker;

class IDungeonMaker {
public:
    virtual void build() = 0;
    [[nodiscard]] virtual std::shared_ptr<Dungeon> getDungeon() const = 0;
};

class Dungeon {
public:
    // dungeon may be built only by DungeonMaker
    Dungeon() : m_rooms(), m_cells() {}

    [[nodiscard]] std::vector<std::shared_ptr<Cell>> getCells() const {
        return m_cells;
    }

    void setTargetRoom(std::shared_ptr<Room> room) {
        m_target_room = room;
    }

    [[nodiscard]] std::vector<std::weak_ptr<Room>> getRooms() const {
        return m_rooms;
    }

    [[nodiscard]] std::weak_ptr<Cell> getCurrentCell() const {
        return m_current_cell;
    }

    void setCurrentCell(std::shared_ptr<Cell> cell) {
        m_current_cell = cell;
    }

    [[nodiscard]] std::weak_ptr<Room> getTargetRoom() const {
        return m_target_room;
    }

    // find rooms which are connected with given room by corridor(cells)
    static std::vector<std::weak_ptr<Room>> getRoomNeighbours(const std::weak_ptr<Room> &room);

    friend class IDungeonMaker;
    friend class MockDungeonMaker;
    friend class DungeonMaker;

private:
    std::vector<std::weak_ptr<Room>> m_rooms;
    std::vector<std::shared_ptr<Cell>> m_cells;

    std::weak_ptr<Cell> m_current_cell;
    std::weak_ptr<Room> m_target_room;
};
}   // namespace dungeon
