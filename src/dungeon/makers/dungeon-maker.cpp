#include "dungeon-maker.h"

using namespace dungeon_matrix;
using namespace dungeon;

void DungeonMaker::build() {
    randint.seed(15);
    DungeonMatrix result = generate_skeleton();
}

DungeonMatrix DungeonMaker::build_matrix() {
    randint.seed(15);
    DungeonMatrix result = generate_skeleton();
    return result;
}

std::shared_ptr<Dungeon> DungeonMaker::getDungeon() const {
    return dungeon;
}

DungeonMatrix DungeonMaker::generate_skeleton() {
    DungeonMatrix result{height, width};

    std::vector<std::pair<coords, coords>> queue;
    generate_room(result, queue, randint(1, height - 2), randint(1, width - 2));

    while (!queue.empty() && result.rooms_count() < max_rooms_count) {
        int queue_i = randint(0, (int)queue.size() - 1);
        int y0 = queue[queue_i].first.first, x0 = queue[queue_i].first.second;
        int y1 = queue[queue_i].second.first, x1 = queue[queue_i].second.second;
        queue.erase(queue.begin() + queue_i);

        if (result.get_cell(y1, x1) == DungeonMatrixCell::Room) {
            result.random_pave(y0, y1, x0, x1, randint);
            continue;
        }
        if (result.get_cell(y1, x1) == DungeonMatrixCell::Corridor) {
            continue;
        }

        coords n = DungeonMatrix::neighbors(y1, x1)[randint(0, 3)];
        int y2 = (n.first - y1) * (int)basic_distance + y1, x2 = (n.second - x1) * (int)basic_distance + x1;

        if (randint(0, 1) == 0 && generate_room(result, queue, y2, x2)) {
            result.random_pave(y0, y1, x0, x1, randint);
            result.random_pave(y1, y2, x1, x2, randint);
            continue;
        } else if (generate_room(result, queue, y1, x1)) {
            result.random_pave(y0, y1, x0, x1, randint);
        }
    }

    return result;
}

bool DungeonMaker::generate_room(DungeonMatrix &mat, std::vector<std::pair<coords, coords>> &queue, int y, int x) {
    if (!mat.generate_room(y, x, true)) return false;

    queue.emplace_back(coords(y, x), coords(y - basic_distance, x));
    queue.emplace_back(coords(y, x), coords(y + basic_distance, x));
    queue.emplace_back(coords(y, x), coords(y, x - basic_distance));
    queue.emplace_back(coords(y, x), coords(y, x + basic_distance));
    return true;
}
