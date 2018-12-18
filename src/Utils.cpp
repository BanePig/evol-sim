#include "Utils.hpp"

double randDouble(double min, double max)
{
    return (std::rand() / (double)RAND_MAX) * (max - min) + min;
}

int randInt(int min, int max)
{
    if(min == max) return max;
    return std::rand() % (max - min) + min;
}