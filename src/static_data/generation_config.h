#pragma once
#include "dungeon/cell/cell.h"
#include <map>

namespace generation_cfg {
    // events generation
    // map dimensions, in cells (room: 3x3 cells, corridor: 1x1 cells)
    static const size_t HEIGHT = 30;
    static const size_t WIDTH = 30;

    static const size_t ROOMS_COUNT = 15;

    static const size_t INITIAL_CORRIDOR_LENGTH = 3;
    static const size_t MIN_CORRIDORS_LENGTH = 2;
    static const size_t MAX_CORRIDORS_LENGTH = 12;

    // number of attempts to move room
    static const size_t ROOMS_NOISE_ITERATIONS = 50;
    // maximum displacement of room along axis, per iteration
    static const size_t ROOMS_NOISE_STRENGTH = 2;

    // number of attempts to move corridor
    static const size_t CORRIDOR_NOISE_ITERATIONS = 50;
    // maximum displacement of corridor along axis, per iteration
    static const size_t CORRIDOR_NOISE_STRENGTH = 2;

    // events generation
    // weights for room types, non-negative integers
    static const std::map<dungeon::CellType, size_t> rooms_weights = {
            {dungeon::CellType::NOTHING, 0},
            {dungeon::CellType::FIGHT, 1},
            {dungeon::CellType::TREASURE, 1},
            {dungeon::CellType::BOSS, 2}
    };
    // limits (by distance in sorted array) for room types, double from 0 to 1
    static const std::map<dungeon::CellType, double> rooms_limits = {
            {dungeon::CellType::NOTHING, 0},
            {dungeon::CellType::FIGHT, 0},
            {dungeon::CellType::TREASURE, 0},
            {dungeon::CellType::BOSS, .5}
    };

    // weights for corridors types, non-negative integers
    static const std::map<dungeon::CellType, size_t> corridors_weights = {
            {dungeon::CellType::NOTHING, 18},
            {dungeon::CellType::FIGHT, 2},
            {dungeon::CellType::TREASURE, 2},
            {dungeon::CellType::TRAP, 1},
            {dungeon::CellType::DOOR, 1},
    };

    // repeats of corridors types are tracked only in this interval
    static const size_t corridors_memory_length = 10;
}
