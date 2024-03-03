#include "randint.h"

using namespace pseudorandom;

void Randint::seed(int seed) {
    random.seed(seed);
}

int Randint::operator()(int le, int ri) {
    unsigned int a = random();
    return le + (int)(a % (ri - le + 1));
}
