#pragma once
#include "dungeon-matrix.h"
#include "dungeon/dungeon.h"
#include "randint.h"
#include <memory>
#include <utility>

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
    static const size_t corridor_noise_strength = 2;

    // random
    unsigned int seed = 0;
    pseudorandom::Randint randint;

    std::shared_ptr<Dungeon> dungeon;

    std::shared_ptr<dungeon_matrix::DungeonMatrix> build_matrix();
    static bool generate_room(const std::shared_ptr<dungeon_matrix::DungeonMatrix> &mat,
                              std::vector<std::pair<dungeon_matrix::coords, dungeon_matrix::coords>> &queue, int y,
                              int x);
    void generate_skeleton(const std::shared_ptr<dungeon_matrix::DungeonMatrix> &mat);
    void room_noise(const std::shared_ptr<dungeon_matrix::DungeonMatrix> &old);
    void corridor_noise(const std::shared_ptr<dungeon_matrix::DungeonMatrix> &old);

public:
    [[nodiscard]] unsigned int getSeed() const;
    void setSeed(unsigned int value);
    void setRandomSeed();

    void build() final;
    [[nodiscard]] std::shared_ptr<Dungeon> getDungeon() const final;
};
}   // namespace dungeon
