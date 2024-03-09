#include "cell.h"

namespace dungeon {
Cell::Cell(dungeon::Position position, bool is_room) : m_position(position), m_is_room(is_room) {}

Room::Room(dungeon::Position position) : Cell(position, true) {}

void connectCells(std::weak_ptr<Cell> cell1, std::weak_ptr<Cell> cell2) {
    cell1.lock()->m_neighbours.push_back(cell2);
    cell2.lock()->m_neighbours.push_back(cell1);
}

void setCellType(std::weak_ptr<Cell> cell, const CellType &type) {
    cell.lock()->m_type = type;
    printf("Cell type: %d\n", cell.lock()->m_type);
}

}   // namespace dungeon
