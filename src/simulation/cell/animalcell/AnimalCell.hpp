#ifndef ANIMAL_CELL_H
#define ANIMAL_CELL_H

#include "../Cell.hpp"

class PlantCell;

class AnimalCell : public Cell
{
    float strength;
    float speed;
    float endurance;
    float movementAngle;

    void move();
    void attackIntersectingPrey();
    bool createChild();
    void attack(Cell* cell);
    void attackAnimal(AnimalCell& animal);
    void attackPlant(PlantCell& plant);

  public:
    AnimalCell(Simulation& parentSimulation, const sf::Vector2f& position, const sf::Color& color, float size, float strength, float speed, float endurance);
    AnimalCell(const AnimalCell&) = delete;
    AnimalCell& operator=(const AnimalCell&) = delete;
    ~AnimalCell();

    void completeTurn() override;
};

#endif // ANIMAL_CELL_H