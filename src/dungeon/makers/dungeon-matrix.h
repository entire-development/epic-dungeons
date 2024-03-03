#pragma once
#include "randint.h"

namespace dungeon_matrix {
    typedef std::pair<int, int> coords;

    template<class T>
    using matrix = std::vector<std::vector<T>>;

    enum class DungeonMatrixCell {
        Empty, Corridor, Room
    };

    class DungeonMatrix final {
    private:
        const size_t height, width;

        std::vector<coords> rooms;

        matrix<bool> mark_flags;
        std::vector<coords> marks;

        void pave_horizontal(int y, int x1, int x2);
        void pave_vertical(int y1, int y2, int x);
    public:
        matrix<DungeonMatrixCell> cells;
        explicit DungeonMatrix(size_t height, size_t width);

        void set_cell(int y, int x, DungeonMatrixCell value);
        [[nodiscard]] DungeonMatrixCell get_cell(int y, int x) const;

        bool generate_room(int y, int x, bool trust);
        void random_pave(int y1, int y2, int x1, int x2, pseudorandom::Randint &randint);

        [[nodiscard]] size_t rooms_count() const;

        static std::vector<coords> neighbors(int y, int x);
    };
}
