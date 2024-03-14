#pragma once

namespace generation_cfg {
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
}
