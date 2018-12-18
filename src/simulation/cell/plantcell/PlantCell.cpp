#include "PlantCell.hpp"
#include <random>
#include "../../../Utils.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../../Simulation.hpp"
#include "../../subdivision/Subdivision.hpp"

PlantCell::PlantCell(Simulation& parentSimulation, const sf::Vector2f& position, const sf::Color& color, float size)
    : Cell(CellType::PLANT, parentSimulation, position, color, size)
{
}

PlantCell::~PlantCell()
{
}



void PlantCell::completeTurn()
{
    this->health += 0.01 / (size + 1);
    if(health > 1.f) health = 1.f;
    if(health == 1.f) createChild();
}

bool PlantCell::createChild()
{
    auto newSize = this->size * randDouble(0.95, 1.05);

    this->health = .5f;

    auto birthAngle = randDouble(0, M_PI * 2);
    auto offsetMultiplier = (M_SQRT2 * (size + newSize));
    auto childXOffset = std::sin(birthAngle) * offsetMultiplier;
    auto childYOffset = std::cos(birthAngle) * offsetMultiplier;

    auto childPos = sf::Vector2f(getPosition().x + childXOffset, getPosition().y + childYOffset);

    if(childPos.x < 0 || childPos.x >= parentSimulation.dimensions.x ||
        childPos.y < 0 || childPos.y >= parentSimulation.dimensions.y) // If cell is outside simulation dimensions
    {
        return false;
    }
    
    auto childHitBox = Rectangle(childPos.x - .5, childPos.y - .5, newSize, newSize);

    for(int x = childPos.x - size / 2; x <= std::ceil(childPos.x + size / 2); x++)
    {
        for(int y = childPos.y - size / 2; y <= std::ceil(childPos.y + size / 2); y++)
        {
            if(x < 0 || x >= parentSimulation.dimensions.x || y < 0 || y >= parentSimulation.dimensions.y) continue;
            auto& subdiv = parentSimulation.subdivisionAt(x, y);

            for(auto cell : subdiv.nearbyCells)
            {
                if(cell == this) continue;
                if(cell->getHitBox().intersects(childHitBox)) 
                    return false;
            }
        }
    }

    auto redMutation = randInt(-2, 2);
    auto greenMutation = randInt(-2, 2);
    auto blueMutation = randInt(-2, 2);

    auto newColor = sf::Color(clamp(color.r + redMutation, 0, 255), clamp(color.g + greenMutation, 0, 255), clamp(color.b + blueMutation, 0, 255));

    new PlantCell(parentSimulation, childPos, newColor, newSize);

    return true;
}