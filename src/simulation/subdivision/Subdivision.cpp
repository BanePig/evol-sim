#include "Subdivision.hpp"

Subdivision::Subdivision(int x, int y)
    : hitBox(Rectangle((float)x, (float)y, 1.f, 1.f))
{
}

Subdivision::~Subdivision()
{
}



const std::list<Cell*> Subdivision::getContainedCells() const
{
    return this->containedCells;
}

const std::list<Cell*> Subdivision::getNearbyCells() const
{
    return this->nearbyCells;
}