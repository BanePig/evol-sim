#ifndef PLANT_CELL_H
#define PLANT_CELL_H

#include "../Cell.hpp"

class AnimalCell;

class PlantCell : public Cell
{
    bool createChild();

    friend class AnimalCell;

  public:
    PlantCell(Simulation& parentSimulation, const sf::Vector2f& position, const sf::Color& color, float size);
    PlantCell(const PlantCell&) = delete;
    PlantCell& operator=(const PlantCell&) = delete;
    ~PlantCell();

    void completeTurn() override;
};

#endif // PLANT_CELL_H