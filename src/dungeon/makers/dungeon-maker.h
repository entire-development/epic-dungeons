#pragma once
#include "dungeon/dungeon.h"
#include "dungeon-matrix.h"
#include "randint.h"
#include <utility>
#include <memory>

namespace dungeon {
    class DungeonMaker final : IDungeonMaker {
    private:
        // settings
        static const size_t width = 50, height = 50;

        static const size_t max_rooms_count = 25;
        static const size_t basic_distance = 6;

        static const size_t rooms_noise_iterations = 50;
        static const size_t rooms_noise_strength = 2;

        static const size_t corridor_noise_iterations = 50;

        // random
        pseudorandom::Randint randint;

        std::shared_ptr<Dungeon> dungeon;
        static bool generate_room(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& mat,
                                  std::vector<std::pair<dungeon_matrix::coords, dungeon_matrix::coords>> &queue, int y, int x);
        void generate_skeleton(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& mat);
        void room_noise(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& old);
    public:
        std::shared_ptr<dungeon_matrix::DungeonMatrix> build_matrix(int seed);
        void build() final;
        [[nodiscard]] std::shared_ptr<Dungeon> getDungeon() const final;
    };
}