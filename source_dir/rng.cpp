// rng.cpp
// implement utility functions that use / return random numbers

#include "rng.hpp"
#include <random>
#include <iostream>

namespace {
    std::mt19937 e;
}

namespace Penna {

void init_rng(unsigned seed) {
    e.seed(seed);
    std::cout << "Using random seed " << seed << ".\n";
}

double random_double() {
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(e);
}

int random_int(int min, int max) {
    static std::uniform_int_distribution<int> dist;
    return dist(e, std::uniform_int_distribution<int>::param_type(min, max));
}

} // namespace Penna