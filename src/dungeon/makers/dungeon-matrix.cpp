#include "dungeon-matrix.h"

using namespace dungeon_matrix;

DungeonMatrix::DungeonMatrix(size_t height, size_t width) : width(width), height(height),
        cells(matrix<DungeonMatrixCell>(height, std::vector<DungeonMatrixCell>(width, DungeonMatrixCell::Empty))),
        mark_flags(matrix<bool>(height, std::vector<bool>(width, false))) {}

bool DungeonMatrix::generate_room(int y, int x, bool trust) {
    if (y < 1 || x < 1 || y >= height - 1 || x >= width - 1) return false;

    if (trust) {
        if (get_cell(y, x) != DungeonMatrixCell::Empty) return false;
    } else {
        for (int dy = -2; dy <= 2; dy++)
            for (int dx = -2; dx <= 2; dx++)
                if (get_cell(y + dy, x + dx) != DungeonMatrixCell::Empty) return false;
    }

    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            set_cell(y + dy, x + dx, DungeonMatrixCell::Room);

    rooms.emplace_back(y, x);
    return true;
}

DungeonMatrixCell DungeonMatrix::get_cell(int y, int x) const {
    if (y < 0 || x < 0 || y >= height || x >= width) return DungeonMatrixCell::Empty;
    return cells[y][x];
}

void DungeonMatrix::set_cell(int y, int x, DungeonMatrixCell value) {
    if (y < 0 || x < 0 || y >= height || x >= width) return;
    cells[y][x] = value;
}

void DungeonMatrix::pave_horizontal(int y, int x1, int x2) {
    if (x1 > x2) std::swap(x1, x2);
    for (int x = x1; x <= x2; x++)
        if (get_cell(y, x) == DungeonMatrixCell::Empty) set_cell(y, x, DungeonMatrixCell::Corridor);
}

void DungeonMatrix::pave_vertical(int y1, int y2, int x) {
    if (y1 > y2) std::swap(y1, y2);
    for (int y = y1; y <= y2; y++)
        if (get_cell(y, x) == DungeonMatrixCell::Empty) set_cell(y, x, DungeonMatrixCell::Corridor);
}

size_t DungeonMatrix::rooms_count() const {
    return rooms.size();
}

void DungeonMatrix::random_pave(int y1, int y2, int x1, int x2, pseudorandom::Randint &randint) {
    if (y1 == y2) { pave_horizontal(y1, x1, x2); return; }
    if (x1 == x2) { pave_vertical(y1, y2, x1); return; }

    if (randint(0, 1) == 0) {
        // by y
        if (y2 < y1) { std::swap(y1, y2); std::swap(x1, x2); }
        int y = randint(y1, y2);
        pave_vertical(y1, y, x1);
        pave_horizontal(y, x1, x2);
        pave_vertical(y, y2, x2);
    } else {
        // by x
        if (x2 < x1) { std::swap(y1, y2); std::swap(x1, x2); }
        int x = randint(x1, x2);
        pave_horizontal(y1, x1, x);
        pave_vertical(y1, y2, x);
        pave_horizontal(y2, x, x2);
    }
}

std::vector<coords> DungeonMatrix::neighbors(int y, int x, int dist) {
    return std::vector<coords>{coords(y - dist, x), coords(y + dist, x), coords(y, x - dist), coords(y, x + dist)};
}

std::vector<coords> DungeonMatrix::corners(int y, int x) {
    return std::vector<coords>{coords(y - 1, x - 1), coords(y + 1, x - 1), coords(y - 1, x + 1), coords(y + 1, x + 1)};
}

coords DungeonMatrix::get_end(int y, int x, coords from) const {
    // (y, x) - corridor
    for (coords n : neighbors(y, x)) {
        if (n == from) continue;
        if (get_cell(n.first, n.second) != DungeonMatrixCell::Corridor) continue;
        return get_end(n.first, n.second, coords(y, x));
    }
    return coords(y, x);
}

std::shared_ptr<std::deque<coords>> DungeonMatrix::get_path(int y, int x, coords from) const {
    // (y, x) - corridor
    for (coords n : neighbors(y, x)) {
        if (n == from) continue;
        if (get_cell(n.first, n.second) != DungeonMatrixCell::Corridor) continue;

        std::shared_ptr<std::deque<coords>> path = get_path(n.first, n.second, coords(y, x));
        path->emplace_front(y, x);
        return path;
    }
    std::shared_ptr<std::deque<coords>> path = std::make_shared<std::deque<coords>>();
    path->emplace_front(y, x);
    return path;
}

bool DungeonMatrix::check_errors(int y, int x, coords from) const {
    if (get_cell(y, x) != DungeonMatrixCell::Corridor) return false;

    for (coords c : corners(y, x)) {
        int corridors_n_count = ((get_cell(y, c.second) == DungeonMatrixCell::Corridor) ? 1 : 0)
                + ((get_cell(c.first, x) == DungeonMatrixCell::Corridor) ? 1 : 0);
        int rooms_n_count = ((get_cell(y, c.second) == DungeonMatrixCell::Room) ? 1 : 0)
                + ((get_cell(c.first, x) == DungeonMatrixCell::Room) ? 1 : 0);

        // check corner touching a corridor
        if (get_cell(c.first, c.second) == DungeonMatrixCell::Corridor && corridors_n_count != 1)
            return true;

        // check corner touching a room
        if (get_cell(c.first, c.second) == DungeonMatrixCell::Room && rooms_n_count == 0 && corridors_n_count != 1)
            return true;
    }

    int corridors_n_count = 0, rooms_n_count = 0;
    for (coords n : neighbors(y, x)) {
        coords c1 = (x == n.second) ? coords(n.first, x - 1) : coords(y - 1, n.second);
        coords c2 = (x == n.second) ? coords(n.first, x + 1) : coords(y + 1, n.second);

        if (get_cell(n.first, n.second) == DungeonMatrixCell::Corridor) {
            corridors_n_count++;
        } else if (get_cell(n.first, n.second) == DungeonMatrixCell::Room) {
            if (get_cell(c1.first, c1.second) == DungeonMatrixCell::Room && get_cell(c2.first, c2.second) == DungeonMatrixCell::Room) {
                rooms_n_count++;
                continue;
            }

            // check touching a room
            if (get_cell(c1.first, c1.second) == DungeonMatrixCell::Room ) {
                if (get_cell(y, c1.second) != DungeonMatrixCell::Corridor && get_cell(c1.first, x) != DungeonMatrixCell::Corridor)
                    return true;
            } else {
                if (get_cell(y, c2.second) != DungeonMatrixCell::Corridor && get_cell(c2.first, x) != DungeonMatrixCell::Corridor)
                    return true;
            }
        }
    }

    // check neighbors count
    if (2 - rooms_n_count != corridors_n_count) return true;

    for (coords n : neighbors(y, x)) {
        if (n == from) continue;
        if (check_errors(n.first, n.second, coords(y, x))) return true;
    }

    return false;
}

coords DungeonMatrix::get_room(int id) const {
    return rooms[id];
}

void DungeonMatrix::erase_room(int id) {
    int y = rooms[id].first, x = rooms[id].second;
    rooms.erase(rooms.begin() + id);

    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            set_cell(y + dy, x + dx, DungeonMatrixCell::Empty);

    for (coords n : neighbors(y, x, 2)) {
        if (get_cell(n.first, n.second) != DungeonMatrixCell::Corridor) continue;
        std::shared_ptr<std::deque<coords>> path = get_path(n.first, n.second);
        for (coords c : *path) set_cell(c.first, c.second, DungeonMatrixCell::Empty);
    }
}
