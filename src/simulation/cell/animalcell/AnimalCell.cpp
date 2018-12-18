#include "../../../Utils.hpp"
#include "../../Simulation.hpp"
#include "../../subdivision/Subdivision.hpp"
#include "../plantcell/PlantCell.hpp"
#include "AnimalCell.hpp"

AnimalCell::AnimalCell(Simulation& parentSimulation, const sf::Vector2f& position,
    const sf::Color& color, float size, float strength, float speed, float endurance)
    : Cell(CellType::ANIMAL, parentSimulation, position, color, size), strength(strength), speed(speed), endurance(endurance),
    movementAngle(randDouble(0, M_PI * 2))
{
}

AnimalCell::~AnimalCell()
{
}

void AnimalCell::completeTurn()
{
    attackIntersectingPrey();
    move();
    attackIntersectingPrey();
    if(health > .75f && randDouble(0.0, 1 - health) < 1.0) createChild();
    this->health -= 0.00166f / endurance; // With an endurance of 1 animal will last 600 ticks.
}

void AnimalCell::attackIntersectingPrey()
{
    for(int x = getPosition().x - size / 2; x <= std::ceil(getPosition().x + size / 2); x++)
    {
        for(int y = getPosition().y - size / 2; y <= std::ceil(getPosition().y + size / 2); y++)
        {
            if(x < 0 || x >= parentSimulation.dimensions.x || y < 0 || y >= parentSimulation.dimensions.y) continue;
            auto& subdiv = parentSimulation.subdivisionAt(x, y);

            for(auto cell : subdiv.getNearbyCells())
            {
                if(cell == this) continue;
                if(cell->getHitBox().intersects(hitBox))
                {
                    this->attack(cell);
                    if(cell->getHealth() < 0)
                    {
                        delete cell;
                    }
                }
            }
        }
    }
}

void AnimalCell::attack(Cell* cell)
{
    switch(cell->type)
    {
      case CellType::PLANT:
        attackPlant(*(PlantCell*)cell);
      case CellType::ANIMAL:
        attackAnimal(*(AnimalCell*)cell);
    }
}

void AnimalCell::attackAnimal(AnimalCell& animal)
{
    if(animal.size > this->size * 1.5f || animal.size < this->size * 0.05f) return;
    auto damage = (this->size * this->strength * health) / (animal.endurance * animal.size * animal.health);
    animal.health -= damage;
    if(animal.health < 0) 
    {
        health += animal.size;
        if(health > 1.f) health = 1.f;
    }
}

void AnimalCell::attackPlant(PlantCell& plant)
{
    if(plant.size > this->size * 1.5f || plant.size < this->size * 0.05f) return;
    auto damage = (this->size * health) / (plant.size);
    plant.health -= damage;
    health += plant.size * clamp(damage, 0.f, 1.f);
    if(health > 1.f) health = 1.f;
}

void AnimalCell::move()
{
    this->movementAngle += randDouble(-0.1, 0.1);
    
    auto xMovement = std::sin(movementAngle) * randDouble(0, speed) * health;
    auto yMovement = std::cos(movementAngle) * randDouble(0, speed) * health;
    
    auto newPos = sf::Vector2f(getPosition().x + xMovement, getPosition().y + yMovement);
    if(newPos.x < 0 || newPos.x >= parentSimulation.dimensions.x || newPos.y < 0 || newPos.y >= parentSimulation.dimensions.y) return;

    this->setPosition(newPos);
}

bool AnimalCell::createChild()
{
    auto newSize = this->size * randDouble(0.95, 1.05);

    this->health = health - .5f;

    auto birthAngle = randDouble(0, M_PI * 2);
    auto offsetMultiplier = (M_SQRT2 * (size/2 + newSize));
    auto childXOffset = std::sin(birthAngle) * offsetMultiplier;
    auto childYOffset = std::cos(birthAngle) * offsetMultiplier;

    auto childPos = sf::Vector2f(getPosition().x + childXOffset, getPosition().y + childYOffset);

    if(childPos.x < 0 || childPos.x >= parentSimulation.dimensions.x ||
        childPos.y < 0 || childPos.y >= parentSimulation.dimensions.y) // If cell is outside simulation dimensions
    {
        return false;
    }
    
    auto childHitBox = Rectangle(childPos.x - .5, childPos.y - .5, newSize, newSize);

    auto redMutation = randInt(-2, 2);
    auto greenMutation = randInt(-2, 2);
    auto blueMutation = randInt(-2, 2);

    auto newColor = sf::Color(clamp(color.r + redMutation, 0, 255), clamp(color.g + greenMutation, 0, 255), clamp(color.b + blueMutation, 0, 255));

    auto newStrength = strength + randDouble(-0.05, 0.05);
    if(newStrength < 0.1f) newStrength = 0.1f;
    auto newSpeed = speed + randDouble(-0.05, 0.05);
    if(newSpeed < 0.1f) newSpeed = 0.1f;
    auto newEndurance = endurance + randDouble(-0.05, 0.05);
    if(newEndurance < 0.1f) newEndurance = 0.1f;

    auto* child = new AnimalCell(parentSimulation, childPos, newColor, newSize, newStrength, newSpeed, newEndurance);
    child->health = 0.1f;

    return true;
}