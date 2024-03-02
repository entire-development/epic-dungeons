#include "dungeon-matrix.h"

namespace dungeon_matrix {
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
                set_cell(y, x, DungeonMatrixCell::Room);

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
        rooms.size();
    }

    void DungeonMatrix::random_pave(int y1, int y2, int x1, int x2, dungeon::Randint &randint) {
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

    std::vector<coords> DungeonMatrix::neighbors(int y, int x) {
        return std::vector<coords>{coords(y - 1, x), coords(y + 1, x), coords(y, x - 1), coords(y, x + 1)};
    }
}
