#pragma once
#include <random>

namespace pseudorandom {
    class Randint final {
    private:
        std::mt19937 random;
    public:
        void seed(unsigned int seed);
        int operator()(int le, int ri);
    };
}