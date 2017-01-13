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

inline int correct(double v) {
    return int(pow(clampf(v), 1/2.2) * 255 + .5);
}

template<typename T>
inline T sq(T v) {
    return v * v;
}

#endif