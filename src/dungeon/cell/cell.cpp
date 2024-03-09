#include "cell.h"

namespace dungeon {
Cell::Cell(dungeon::Position position, bool is_room) : m_position(position), m_is_room(is_room) {}

Room::Room(dungeon::Position position) : Cell(position, true) {}

Direction getDirection(std::shared_ptr<Cell> from, std::shared_ptr<Cell> to) {
    int dx = to->getPosition().first - from->getPosition().first;
    int dy = to->getPosition().second - from->getPosition().second;
    if (dx == 0 && dy == -1 || dx == 0 && dy == -2) {
        return Direction::UP;
    } else if (dx == 1 && dy == 0 || dx == 2 && dy == 0) {
        return Direction::RIGHT;
    } else if (dx == 0 && dy == 1 || dx == 0 && dy == 2) {
        return Direction::DOWN;
    } else if (dx == -1 && dy == 0 || dx == -2 && dy == 0) {
        return Direction::LEFT;
    }

    return Direction::NONE;
}

std::weak_ptr<Cell> Cell::getNeighbour(const Direction &direction) {
    for (auto &neighbour : m_neighbours) {
        if (getDirection(shared_from_this(), neighbour.lock()) == direction) {
            return neighbour;
        }
    }
    return std::weak_ptr<Cell>();
}

void connectCells(std::weak_ptr<Cell> cell1, std::weak_ptr<Cell> cell2) {
    cell1.lock()->m_neighbours.push_back(cell2);
    cell2.lock()->m_neighbours.push_back(cell1);
}

void setCellType(std::weak_ptr<Cell> cell, const CellType &type) {
    cell.lock()->m_type = type;
}

}   // namespace dungeon
