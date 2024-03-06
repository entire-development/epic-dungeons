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

    std::shared_ptr<events::Event> getEvent();
    std::vector<std::weak_ptr<Cell>> getNeighbours();

    friend void connectCells(std::weak_ptr<Cell> cell1, std::weak_ptr<Cell> cell2);

private:
    const Position m_position;
    const bool m_is_room;

    bool m_is_visited = false;
    bool m_is_discovered = false;

    std::shared_ptr<events::Event> m_event = nullptr;
    std::vector<std::weak_ptr<Cell>> m_neighbours;
};

class Room : public Cell {};

void connectCells(std::weak_ptr<Cell> cell1, std::weak_ptr<Cell> cell2);
}   // namespace dungeon
