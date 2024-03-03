#include "dungeon-maker.h"

using namespace dungeon_matrix;
using namespace dungeon;

void DungeonMaker::build() {
    randint.seed(16;
    std::shared_ptr<DungeonMatrix> result = std::make_shared<DungeonMatrix>(height, width);

    generate_skeleton(result);

    for (int i = 0; i < rooms_noise_iterations; i++)
        room_noise(result);
}

std::shared_ptr<DungeonMatrix> DungeonMaker::build_matrix(int seed) {
    randint.seed(seed);
    std::shared_ptr<DungeonMatrix> result = std::make_shared<DungeonMatrix>(height, width);

    generate_skeleton(result);

    for (int i = 0; i < rooms_noise_iterations; i++)
        room_noise(result);

    return result;
}

std::shared_ptr<Dungeon> DungeonMaker::getDungeon() const {
    return dungeon;
}

void DungeonMaker::generate_skeleton(const std::shared_ptr<dungeon_matrix::DungeonMatrix>& mat) {
    std::vector<std::pair<coords, coords>> queue;
    generate_room(mat, queue, randint(1, height - 2), randint(1, width - 2));

    while (!queue.empty() && mat->rooms_count() < max_rooms_count) {
        int queue_i = randint(0, (int)queue.size() - 1);
        int y0 = queue[queue_i].first.first, x0 = queue[queue_i].first.second;
        int y1 = queue[queue_i].second.first, x1 = queue[queue_i].second.second;
        queue.erase(queue.begin() + queue_i);

        if (mat->get_cell(y1, x1) == DungeonMatrixCell::Room) {
            mat->random_pave(y0, y1, x0, x1, randint);
            continue;
        }
        if (mat->get_cell(y1, x1) == DungeonMatrixCell::Corridor) {
            continue;
        }

        coords n = DungeonMatrix::neighbors(y1, x1)[randint(0, 3)];
        int y2 = (n.first - y1) * (int)basic_distance + y1, x2 = (n.second - x1) * (int)basic_distance + x1;

        if (randint(0, 1) == 0 && generate_room(mat, queue, y2, x2)) {
            mat->random_pave(y0, y1, x0, x1, randint);
            mat->random_pave(y1, y2, x1, x2, randint);
            continue;
        } else if (generate_room(mat, queue, y1, x1)) {
            mat->random_pave(y0, y1, x0, x1, randint);
        }
    }
}

bool DungeonMaker::generate_room(const std::shared_ptr<DungeonMatrix>& mat, std::vector<std::pair<coords, coords>> &queue, int y, int x) {
    if (!mat->generate_room(y, x, true)) return false;

    queue.emplace_back(coords(y, x), coords(y - basic_distance, x));
    queue.emplace_back(coords(y, x), coords(y + basic_distance, x));
    queue.emplace_back(coords(y, x), coords(y, x - basic_distance));
    queue.emplace_back(coords(y, x), coords(y, x + basic_distance));
    return true;
}

void DungeonMaker::room_noise(std::shared_ptr<DungeonMatrix> old) {
    std::shared_ptr<DungeonMatrix> mat = std::make_shared<DungeonMatrix>(*old);
    int room_id = randint(0, (int)mat->rooms_count() - 1);
    coords old_place = mat->get_room(room_id);

    int dy = randint(-(int)rooms_noise_strength, rooms_noise_strength),
        dx = randint(-(int)rooms_noise_strength, rooms_noise_strength);

    std::vector<std::pair<coords, coords>> pairs;
    for (coords n : mat->neighbors(old_place.first, old_place.second, 2)) {
        if (mat->get_cell(n.first, n.second) != DungeonMatrixCell::Corridor) continue;
        pairs.emplace_back(coords(n.first + dy, n.second + dx), mat->get_end(n.first, n.second));
    }

    mat->erase_room(room_id);
    if (!mat->generate_room(old_place.first + dy, old_place.second + dx, false)) return;

    for (std::pair<coords, coords> pair : pairs) {
        mat->random_pave(pair.first.first, pair.second.first, pair.first.second, pair.second.second, randint);
        if (mat->check_errors(pair.first.first, pair.first.second)) return;
        if (mat->get_end(pair.first.first, pair.first.second) != pair.second) return;
    }

    old.swap(mat);
}
