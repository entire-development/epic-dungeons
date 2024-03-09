#include "dungeon-maker.h"
#include <ctime>

using namespace dungeon_matrix;
using namespace dungeon;

void DungeonMaker::build() {
    std::shared_ptr<DungeonMatrix> mat = build_matrix();

    dungeon = std::make_shared<Dungeon>();
    std::vector<std::vector<std::shared_ptr<Cell>>> cells(height, std::vector<std::shared_ptr<Cell>>(width));

    for (int room_id = 0; room_id < mat->rooms_count(); room_id++) {
        coords room_coords = mat->get_room(room_id);
        std::shared_ptr<Room> room = std::make_shared<Room>(room_coords);
        CellType type = (rand() % 2) ? CellType::SHOP : CellType::FIGHT;
        setCellType(room, type);
        dungeon->m_cells.push_back(room);
        dungeon->m_rooms.push_back(room);

        for (coords n : mat->neighbors(room_coords.first, room_coords.second, 2)) {
            if (mat->get_cell(n.first, n.second) != DungeonMatrixCell::Corridor)
                continue;
            if (cells[n.first][n.second] == nullptr) {
                std::shared_ptr<std::deque<coords>> path = mat->get_path(n.first, n.second);

                for (int i = 0; i < path->size(); i++) {
                    auto cell = std::make_shared<Cell>((*path)[i]);
                    dungeon->m_cells.push_back(cell);

                    if (i != 0)
                        connectCells(dungeon->m_cells.back(), dungeon->m_cells[dungeon->m_cells.size() - 2]);
                    cells[(*path)[i].first][(*path)[i].second] = dungeon->m_cells.back();
                }
            }
            connectCells(room, cells[n.first][n.second]);
        }
    }

    dungeon->m_current_cell = dungeon->m_rooms[0];
}

std::shared_ptr<DungeonMatrix> DungeonMaker::build_matrix() {
    randint.seed(seed);
    size_t h = height, w = width;
    std::shared_ptr<DungeonMatrix> result = std::make_shared<DungeonMatrix>(h, w);

    generate_skeleton(result);

    for (int i = 0; i < rooms_noise_iterations; i++)
        room_noise(result);

    for (int i = 0; i < corridor_noise_iterations; i++)
        corridor_noise(result);

    return result;
}

std::shared_ptr<Dungeon> DungeonMaker::getDungeon() const {
    return dungeon;
}

void DungeonMaker::generate_skeleton(const std::shared_ptr<dungeon_matrix::DungeonMatrix> &mat) {
    std::vector<std::pair<coords, coords>> queue;
    generate_room(mat, queue, randint(1, height - 2), randint(1, width - 2));

    while (!queue.empty() && mat->rooms_count() < max_rooms_count) {
        int queue_i = randint(0, (int) queue.size() - 1);
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
        int y2 = (n.first - y1) * (int) basic_distance + y1, x2 = (n.second - x1) * (int) basic_distance + x1;

        if (randint(0, 1) == 0 && generate_room(mat, queue, y2, x2)) {
            mat->random_pave(y0, y1, x0, x1, randint);
            mat->random_pave(y1, y2, x1, x2, randint);
            continue;
        } else if (generate_room(mat, queue, y1, x1)) {
            mat->random_pave(y0, y1, x0, x1, randint);
        }
    }
}

bool DungeonMaker::generate_room(const std::shared_ptr<DungeonMatrix> &mat,
                                 std::vector<std::pair<coords, coords>> &queue, int y, int x) {
    if (!mat->generate_room(y, x, true))
        return false;

    queue.emplace_back(coords(y, x), coords(y - basic_distance, x));
    queue.emplace_back(coords(y, x), coords(y + basic_distance, x));
    queue.emplace_back(coords(y, x), coords(y, x - basic_distance));
    queue.emplace_back(coords(y, x), coords(y, x + basic_distance));
    return true;
}

void DungeonMaker::room_noise(const std::shared_ptr<DungeonMatrix> &old) {
    std::shared_ptr<DungeonMatrix> mat = std::make_shared<DungeonMatrix>(*old);
    int room_id = randint(0, (int) mat->rooms_count() - 1);
    coords old_place = mat->get_room(room_id);

    int dy = randint(-(int) rooms_noise_strength, rooms_noise_strength),
        dx = randint(-(int) rooms_noise_strength, rooms_noise_strength);

    std::vector<std::pair<coords, coords>> pairs;
    for (coords n : mat->neighbors(old_place.first, old_place.second, 2)) {
        if (mat->get_cell(n.first, n.second) != DungeonMatrixCell::Corridor)
            continue;
        pairs.emplace_back(coords(n.first + dy, n.second + dx), mat->get_end(n.first, n.second));
    }

    mat->erase_room(room_id);
    if (!mat->generate_room(old_place.first + dy, old_place.second + dx, false))
        return;

    for (std::pair<coords, coords> pair : pairs) {
        mat->random_pave(pair.first.first, pair.second.first, pair.first.second, pair.second.second, randint);
        if (mat->check_errors(pair.first.first, pair.first.second))
            return;
        if (mat->get_end(pair.first.first, pair.first.second) != pair.second)
            return;
    }

    *old = *mat;
}

void DungeonMaker::corridor_noise(const std::shared_ptr<dungeon_matrix::DungeonMatrix> &old) {
    std::shared_ptr<DungeonMatrix> mat = std::make_shared<DungeonMatrix>(*old);
    coords room = mat->get_room(randint(0, (int) mat->rooms_count() - 1));

    std::vector<coords> starts;
    for (coords n : mat->neighbors(room.first, room.second, 2)) {
        if (mat->get_cell(n.first, n.second) != DungeonMatrixCell::Corridor)
            continue;
        starts.push_back(n);
    }

    coords start = starts[randint(0, (int) starts.size() - 1)];
    std::shared_ptr<std::deque<coords>> path = mat->get_path(start.first, start.second);

    if (path->size() < 5)
        return;

    int mid_id = randint(1, (int) path->size() - 2);
    int start_id = randint(0, mid_id - 1), end_id = randint(mid_id + 1, (int) path->size() - 1);

    for (int i = start_id; i < end_id; i++)
        mat->set_cell((*path)[i].first, (*path)[i].second, DungeonMatrixCell::Empty);
    int y = (*path)[mid_id].first + randint(-(int) corridor_noise_strength, corridor_noise_strength),
        x = (*path)[mid_id].second + randint(-(int) corridor_noise_strength, corridor_noise_strength);

    if (y < 0 || x < 0 || y >= height || x >= width)
        return;

    mat->random_pave((*path)[start_id].first, y, (*path)[start_id].second, x, randint);
    mat->random_pave((*path)[end_id].first, y, (*path)[end_id].second, x, randint);

    if (mat->check_errors(start.first, start.second))
        return;
    if (mat->get_end(start.first, start.second) != (*path)[path->size() - 1])
        return;

    if (mat->check_errors(y, x))
        return;
    coords end = mat->get_end(y, x);
    if (end != start && end != (*path)[path->size() - 1])
        return;

    *old = *mat;
}

unsigned int DungeonMaker::getSeed() const {
    return seed;
}

void DungeonMaker::setSeed(unsigned int value) {
    seed = value;
}

void DungeonMaker::setRandomSeed() {
    seed = std::time(nullptr);
}
