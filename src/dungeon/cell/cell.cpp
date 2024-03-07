#include "cell.h"

dungeon::Cell::Cell(dungeon::Position position, bool is_room) : m_position(position), m_is_room(is_room) {}

dungeon::Room::Room(dungeon::Position position) : Cell(position, true) {}
