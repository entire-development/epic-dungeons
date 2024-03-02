#pragma once
#include "dungeon/dungeon.h"
#include "dungeon-matrix.h"
#include <random>

namespace dungeon {
    using namespace dungeon_matrix;

    class Randint final {
    private:
        std::mt19937 random;
    public:
        void seed(int seed);
        int operator()(int le, int ri);
    };

    class DungeonMaker final : IDungeonMaker {
    private:
        // settings
        static const size_t width = 30, height = 30;
        static const size_t max_rooms_count = 15;
        static const size_t basic_distance = 6;

        // random
        Randint randint;

        std::shared_ptr<Dungeon> dungeon;
        static bool generate_room(DungeonMatrix &mat, std::vector<std::pair<coords, coords>> &queue, int y, int x);
        const DungeonMatrix &generate_skeleton();
    public:
        void build() final;
        [[nodiscard]] std::shared_ptr<Dungeon> getDungeon() const final;
    };
}