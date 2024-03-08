#include "MockDungeonMaker.h"
#include <assert.h>
#include <memory>

namespace dungeon {
void dungeon::MockDungeonMaker::build() {
    dungeon = std::make_shared<Dungeon>();

    std::vector<std::shared_ptr<Room>> rooms = {
        std::make_shared<Room>(Position(20, 25)), std::make_shared<Room>(Position(29, 29)),
        std::make_shared<Room>(Position(24, 20)), std::make_shared<Room>(Position(25, 25)),
        std::make_shared<Room>(Position(29, 24)), std::make_shared<Room>(Position(22, 30)),
    };

    std::vector<std::shared_ptr<Cell>> cells = {
        std::make_shared<Cell>(Position(22, 25)),   // 0
        std::make_shared<Cell>(Position(25, 23)),   // 1
        std::make_shared<Cell>(Position(24, 28)),   // 2
        std::make_shared<Cell>(Position(20, 28)),   // 3
        rooms[0],                                   // 4
        std::make_shared<Cell>(Position(20, 29)),   // 5
        std::make_shared<Cell>(Position(20, 30)),   // 6
        rooms[1],                                   // 7
        std::make_shared<Cell>(Position(27, 24)),   // 8
        std::make_shared<Cell>(Position(29, 21)),   // 9
        std::make_shared<Cell>(Position(29, 20)),   // 10
        std::make_shared<Cell>(Position(27, 20)),   // 11
        std::make_shared<Cell>(Position(24, 22)),   // 12
        rooms[2],                                   // 13
        rooms[3],                                   // 14
        rooms[4],                                   // 15
        std::make_shared<Cell>(Position(27, 25)),   // 16
        std::make_shared<Cell>(Position(25, 27)),   // 17
        std::make_shared<Cell>(Position(24, 29)),   // 18
        std::make_shared<Cell>(Position(24, 30)),   // 19
        std::make_shared<Cell>(Position(20, 27)),   // 20
        std::make_shared<Cell>(Position(24, 23)),   // 21
        std::make_shared<Cell>(Position(23, 25)),   // 22
        std::make_shared<Cell>(Position(25, 28)),   // 23
        std::make_shared<Cell>(Position(29, 22)),   // 24
        std::make_shared<Cell>(Position(29, 27)),   // 25
        std::make_shared<Cell>(Position(29, 26)),   // 26
        std::make_shared<Cell>(Position(26, 20)),   // 27
        std::make_shared<Cell>(Position(28, 20)),   // 28
        rooms[5],                                   // 29
    };

    for (size_t i = 0; i < cells.size(); i++) {
        for (size_t j = i + 1; j < cells.size(); j++) {
            std::shared_ptr<Cell> cell1 = cells[i];
            std::shared_ptr<Cell> cell2 = cells[j];
            int dx = std::abs(cell1->getPosition().first - cell2->getPosition().first);
            int dy = std::abs(cell1->getPosition().second - cell2->getPosition().second);

            if (cell1->isRoom()) {
                if (((dx == 0 && dy == 2) || (dx == 2 && dy == 0))) {
                    assert(!cell2->isRoom());
                    connectCells(cell1, cell2);
                }
            } else {
                if (cell2->isRoom() && ((dx == 0 && dy == 2) || (dx == 2 && dy == 0))) {
                    connectCells(cell1, cell2);
                }
                if (!cell2->isRoom() && ((dx == 0 && dy == 1) || (dx == 1 && dy == 0))) {
                    connectCells(cell1, cell2);
                }
            }
        }
    }

    dungeon->m_cells = cells;
    dungeon->m_rooms.reserve(rooms.size());
    for (auto &room : rooms) {
        dungeon->m_rooms.push_back(room);
    }

    dungeon->m_current_cell = dungeon->m_cells[14];
}

std::shared_ptr<Dungeon> MockDungeonMaker::getDungeon() {
    return dungeon;
}
}   // namespace dungeon
