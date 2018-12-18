#ifndef UTILS_H
#define UTILS_H

#include <random>

template<typename T>
T clamp(T n, T min, T max)
{
    if(n > max) return max;
    if(n < min) return min;
    return n;
}

double randDouble(double min, double max);

int randInt(int min, int max);

#endif // UTILS_H