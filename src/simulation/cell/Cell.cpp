#include "Cell.hpp"
#include <cmath>
#include "../subdivision/Subdivision.hpp"
#include "../Simulation.hpp"

Cell::Cell(CellType type, Simulation& parentSimulation, const sf::Vector2f& position, const sf::Color& color, float size)
    : type(type), parentSimulation(parentSimulation), position(position), color(color), size(size), health(1.f),
    hitBox(Rectangle(position.x - .5, position.y - .5, size, size))
{
    updateNearbySubdivisions();
    auto& newSubdivision = parentSimulation.subdivisionAt(position.x, position.y);
    newSubdivision.containedCells.push_back(this);
    this->containingSubdivision = &newSubdivision;

    parentSimulation.cells.push_back(this);
}

Cell::~Cell()
{
    for(auto subdiv : nearbySubdivisions)
    {
        subdiv->nearbyCells.remove(this);
    }
    containingSubdivision->containedCells.remove(this);
    
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

void Cell::updateNearbySubdivisions()
{
    for(auto subdiv : nearbySubdivisions)
    {
        subdiv->nearbyCells.remove(this);
    }
    nearbySubdivisions.empty();
    for(int x = position.x - size / 2; x <= std::ceil(position.x + size / 2); x++)
    {
        for(int y = position.y - size / 2; y <= std::ceil(position.y + size / 2); y++)
        {
            if(x < 0 || x >= parentSimulation.dimensions.x || y < 0 || y >= parentSimulation.dimensions.y) continue;
            auto& newSubdivision = parentSimulation.subdivisionAt(x, y);
            newSubdivision.nearbyCells.push_back(this);
            this->nearbySubdivisions.push_back(&newSubdivision);
        }
    }
}
void Cell::updateContainingSubdivision()
{
    containingSubdivision->containedCells.remove(this);
    auto& newSubdivision = parentSimulation.subdivisionAt(position.x, position.y);
    newSubdivision.containedCells.push_back(this);
    this->containingSubdivision = &newSubdivision;
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
    position = pos;
    hitBox.x = pos.x - .5;
    hitBox.y = pos.y - .5;
    updateNearbySubdivisions();
    updateContainingSubdivision();
}