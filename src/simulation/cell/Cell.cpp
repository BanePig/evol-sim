#include "Cell.hpp"
#include <cmath>
#include "../subdivision/Subdivision.hpp"
#include "../Simulation.hpp"

Cell::Cell(CellType type, Simulation& parentSimulation, const sf::Vector2f& position, const sf::Color& color, float size)
    : type(type), parentSimulation(parentSimulation), position(position), color(color), size(size), health(1.f),
    hitBox(Rectangle(position.x - .5, position.y - .5, size, size))
{
    updateSubdivisionSignature();
    parentSimulation.cells.push_back(this);
}

Cell::~Cell()
{
    removeSubdivisionSignature();
    parentSimulation.cells.remove(this);
}



void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto& scale = parentSimulation.scale;
    auto rect = sf::RectangleShape(sf::Vector2f(size * scale, size * scale));
    rect.setPosition(hitBox.x * scale, hitBox.y * scale);
    rect.setFillColor(color);
    target.draw(rect);
}

void Cell::removeSubdivisionSignature()
{
    /*parentSimulation.subdivisionAt(position.x, position.y).containedCells.remove(this);
    for(int x = position.x - size / 2; x <= std::ceil(position.x + size / 2); x++)
    {
        for(int y = position.y - size / 2; y <= std::ceil(position.y + size / 2); y++)
        {
            if(x < 0 || x >= parentSimulation.dimensions.x || y < 0 || y >= parentSimulation.dimensions.y) continue;
            parentSimulation.subdivisionAt(x, y).nearbyCells.remove(this);
        }
    }*/

    for(auto subdiv : parentSimulation.subdivisions)
    {
        subdiv->containedCells.remove(this);
        subdiv->nearbyCells.remove(this);
    }
}
void Cell::updateSubdivisionSignature()
{
    /*parentSimulation.subdivisionAt(position.x, position.y).containedCells.push_back(this);
    for(int x = position.x - size / 2; x <= std::ceil(position.x + size / 2); x++)
    {
        for(int y = position.y - size / 2; y <= std::ceil(position.y + size / 2); y++)
        {
            if(x < 0 || x >= parentSimulation.dimensions.x || y < 0 || y >= parentSimulation.dimensions.y) continue;
            parentSimulation.subdivisionAt(x, y).nearbyCells.push_back(this);
        }
    }*/

    for(auto subdiv : parentSimulation.subdivisions)
    {
        subdiv->containedCells.remove(this);
        subdiv->nearbyCells.remove(this);
    }
}



const sf::Color& Cell::getColor() const
{
    return color;
}

float Cell::getHealth() const
{
    return health;
}

float Cell::getSize() const
{
    return size;
}

const Rectangle& Cell::getHitBox() const
{
    return hitBox;
}

const sf::Vector2f& Cell::getPosition() const 
{
    return position;
}

void Cell::setPosition(const sf::Vector2f& pos)
{
    removeSubdivisionSignature();
    position = pos;
    hitBox.x = pos.x - .5;
    hitBox.y = pos.y - .5;
    updateSubdivisionSignature();
}