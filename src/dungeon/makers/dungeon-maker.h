#pragma once
#include "dungeon/dungeon.h"
#include "dungeon-matrix.h"
#include "randint.h"
#include <utility>

namespace dungeon {
    class DungeonMaker final : IDungeonMaker {
    private:
        // settings
        static const size_t width = 50, height = 50;
        static const size_t max_rooms_count = 25;
        static const size_t basic_distance = 6;

        // random
        pseudorandom::Randint randint;

        std::shared_ptr<Dungeon> dungeon;
        static bool generate_room(dungeon_matrix::DungeonMatrix &mat,
                std::vector<std::pair<dungeon_matrix::coords, dungeon_matrix::coords>> &queue, int y, int x);
        dungeon_matrix::DungeonMatrix generate_skeleton();
    public:
        dungeon_matrix::DungeonMatrix build_matrix(int seed);
        void build() final;
        [[nodiscard]] std::shared_ptr<Dungeon> getDungeon() const final;
    };
}