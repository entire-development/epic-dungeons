#include <stdexcept>
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

    for (int i = 0; i < 4; i++) {
        std::weak_ptr<Cell> neighbour = room_shared->getNeighbour(static_cast<Direction>(i));
        if (!neighbour.expired()) {
            std::weak_ptr<Room> neighbour_room = findNextRoom(room, neighbour);
            if (!neighbour_room.expired())
                neighbours[i] = neighbour_room;
        }
    }

    return neighbours;
}

std::weak_ptr<Cell> Dungeon::getNextOnPath() const {
    std::shared_ptr<Cell> current = m_current_cell.lock();
    std::shared_ptr<Room> target = m_target_room.lock();

    for (auto &cell : current->getNeighbours()) {
        if (findNextRoom(current, cell).lock() == target)
            return cell;
    }
    throw std::runtime_error("No path to target room");
}

std::weak_ptr<Cell> Dungeon::getPrevOnPath() const {
    std::shared_ptr<Cell> current = m_current_cell.lock();
    std::shared_ptr<Room> target = m_target_room.lock();

    if (current->isRoom()) {
        throw std::runtime_error("Current cell is room");
    }

    for (auto &cell : current->getNeighbours()) {
        if (findNextRoom(current, cell).lock() != target)
            return cell;
    }
    throw std::runtime_error("No path to target room");
}

uint32_t Dungeon::getDistanceToTarget() const {
    std::shared_ptr<Cell> from_shared = m_current_cell.lock();
    std::shared_ptr<Cell> to_shared = m_target_room.lock();
    std::shared_ptr<Cell> next = getNextOnPath().lock();

    uint32_t distance = 1;
    while (next != to_shared) {
        int next_idx = next->getNeighbours()[0].lock() == from_shared;
        from_shared = next;
        next = next->getNeighbours()[next_idx].lock();
        distance++;
    }

    return distance;
}

}   // namespace dungeon
