#pragma once

#include "events/event.h"
#include <memory>
#include <utility>
#include <vector>

namespace dungeon {
typedef std::pair<int, int> Position;
class Room;

class Cell {
    friend class Dungeon;

public:
    explicit Cell(Position position, bool is_room = false);
    virtual ~Cell() = default;

    constexpr Position getPosition() const {
        return m_position;
    }

    constexpr bool isRoom() const {
        return m_is_room;
    }

    bool isVisited() const {
        return m_is_visited;
    }

    bool isDiscovered() const {
        return m_is_discovered;
    }

    std::shared_ptr<events::Event> getEvent() {
        return m_event;
    }

    std::vector<std::weak_ptr<Cell>> getNeighbours() {
        return m_neighbours;
    }

    friend void connectCells(std::weak_ptr<Cell> cell1, std::weak_ptr<Cell> cell2);

private:
    const Position m_position;
    const bool m_is_room;

    bool m_is_visited = false;
    bool m_is_discovered = false;

    std::shared_ptr<events::Event> m_event = nullptr;
    std::vector<std::weak_ptr<Cell>> m_neighbours;
};

class Room : public Cell {
public:
    explicit Room(Position position);
};

void connectCells(std::weak_ptr<Cell> cell1, std::weak_ptr<Cell> cell2);
}   // namespace dungeon
