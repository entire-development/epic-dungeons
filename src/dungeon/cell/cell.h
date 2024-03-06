#pragma once

#include "events/event.h"
#include <vector>

namespace dungeon {
typedef std::pair<int, int> Position;

class Cell {
public:
    Cell(Position position, bool is_room = false);
    constexpr Position getPosition() const;
    constexpr bool isRoom() const;

    bool isVisited() const;
    bool isDiscovered() const;

    events::Event *getEvent();
    std::vector<std::weak_ptr<Cell>> getNeighbours();

    friend void connectCells(Cell *cell1, Cell *cell2);

private:
    const Position m_position;
    const bool m_is_room;

    bool m_is_visited = false;
    bool m_is_discovered = false;

    events::Event *m_event = nullptr;
    std::vector<std::weak_ptr<Cell>> m_neighbours;
};

class Room : public Cell {};

void connectCells(Cell *cell1, Cell *cell2);
}   // namespace dungeon
