#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include <random>

#define DBL_MAX std::numeric_limits<double>::max()
#define INT_MAX std::numeric_limits<int>::max()
#define randd() ((double)rand() / RAND_MAX)

template<typename T>
inline T clampf(T v) {
    return v > 1 ? 1 : v < 0 ? 0 : v;
}

#endif