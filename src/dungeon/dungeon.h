#pragma once
#include "cell/cell.h"
#include <vector>

namespace dungeon {
class Dungeon {
  public:
  Dungeon();

  std::vector<Room *> getRooms();
  Cell *getCurrentCell();

  // find rooms which are connected with given room by corridor(cells)
  std::vector<Room *> getRoomNeighbours(Room *room);

  private:
  void generate(int seed);

  std::vector<Room *> m_rooms;
  std::vector<Cell *> m_cells;

  Cell *m_current_cell = nullptr;
};
} // namespace dungeon