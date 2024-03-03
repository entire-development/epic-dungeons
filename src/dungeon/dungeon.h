#pragma once
#include "cell/cell.h"
#include <vector>
#include <memory>

namespace dungeon {
    class Dungeon;

    class IDungeonMaker {
    public:
        virtual void build() = 0;
        [[nodiscard]] virtual std::shared_ptr<Dungeon> getDungeon() const = 0;
    };

    class Dungeon {
    public:
        std::vector<Room *> getRooms();
        Cell *getCurrentCell();

        // find rooms which are connected with given room by corridor(cells)
        std::vector<Room *> getRoomNeighbours(Room *room);

        friend class IDungeonMaker;

    private:
        // dungeon may be built only by DungeonMaker
        Dungeon() = default;

        std::vector<Room *> m_rooms;
        std::vector<Cell *> m_cells;

        Cell *m_current_cell = nullptr;
    };
}
