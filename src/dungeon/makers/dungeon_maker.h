#pragma once
#include "dungeon/dungeon.h"
#include "dungeon_matrix.h"
#include "randint.h"
#include <utility>
#include <memory>

namespace dungeon {
    class DungeonMaker final : IDungeonMaker {
    private:
        // random
        unsigned int seed = 0;
        pseudorandom::Randint randint;

        std::shared_ptr<Dungeon> dungeon;

        std::shared_ptr<dungeon_matrix::DungeonMatrix> build_matrix();
        static bool generate_room(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& mat,
                                  std::vector<std::pair<dungeon_matrix::coords, dungeon_matrix::coords>> &queue, int y, int x);
        void generate_skeleton(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& mat);
        void room_noise(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& old);
        void corridor_noise(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& old);
    public:
        [[nodiscard]] unsigned int getSeed() const;
        void setSeed(unsigned int value);
        void setRandomSeed();

        void build() final;
        [[nodiscard]] std::shared_ptr<Dungeon> getDungeon() const final;
    };
}