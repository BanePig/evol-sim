#include "Simulation.hpp"
#include "subdivision/Subdivision.hpp"

Simulation::Simulation(sf::Vector2u dimensions)
    : dimensions(dimensions), scale(1.f)
{
    subdivisions.reserve(dimensions.x * dimensions.y);
    for(int x = 0; x < dimensions.x; x++)
    {
        for(int y = 0; y < dimensions.y; y++)
        {
            subdivisions.push_back(new Subdivision(x, y));
        }
    }
}

Simulation::~Simulation()
{
    for(auto subdivision : subdivisions)
    {
        delete subdivision;
    }
}

void Simulation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto cell : this->cells)
    {
        target.draw(*cell);
    }
}

void Simulation::completeTurns()
{
    for(auto cell : cells)
    {
        if(cell->getHealth() < 0)
        {
            delete cell;
            continue;
        }
        cell->completeTurn();
    }
}

///////////////////////////
// GETTERS AND SETTERS
///////////////////////////

Subdivision& Simulation::subdivisionAt(int x, int y) const
{
    return *(subdivisions[x + y * dimensions.x]);
}

const std::list<Cell*> Simulation::getAllCells() const
{
    return cells;
}

float Simulation::getScale() const
{
    return scale;
}

void Simulation::setScale(float value)
{
    this->scale = value;
}