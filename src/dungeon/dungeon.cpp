#include "dungeon.h"

namespace dungeon {
std::weak_ptr<Room> findNextRoom(std::weak_ptr<Cell> prev, std::weak_ptr<Cell> cur) {
    std::shared_ptr<Cell> prev_shared = prev.lock();
    std::shared_ptr<Cell> cur_shared = cur.lock();

    if (cur_shared->isRoom())   // if cur is room, return it
        return std::dynamic_pointer_cast<Room>(cur_shared);

    for (auto &cell : cur_shared->getNeighbours()) {
        if (cell.lock() == prev_shared)
            continue;
        if (cell.lock()->isRoom())
            return std::dynamic_pointer_cast<Room>(cell.lock());
        return findNextRoom(cur, cell);
    }

    // unreachable code
    return std::weak_ptr<Room>();
}

std::vector<std::weak_ptr<Room>> Dungeon::getRoomNeighbours(const std::weak_ptr<Room> &room) {
    std::vector<std::weak_ptr<Room>> neighbours(4);
    std::shared_ptr<Room> room_shared = room.lock();

    for (auto &cell : room_shared->getNeighbours()) {
        std::shared_ptr<Cell> cell_shared = cell.lock();
        int dx = cell_shared->getPosition().first - room_shared->getPosition().first;
        int dy = cell_shared->getPosition().second - room_shared->getPosition().second;
        int idx = 0;
        if (dx == 0 && dy == -2) {   // up
            idx = 0;
        } else if (dx == 2 && dy == 0) {   // right
            idx = 1;
        } else if (dx == 0 && dy == 2) {   // down
            idx = 2;
        } else if (dx == -2 && dy == 0) {   // left
            idx = 3;
        }

        std::weak_ptr<Room> next_room = findNextRoom(room_shared, cell.lock());
        if (!next_room.expired()) {
            neighbours[idx] = next_room;
        }
    }

    return neighbours;
}

}   // namespace dungeon
