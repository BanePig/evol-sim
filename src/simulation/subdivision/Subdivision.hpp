#ifndef SUBDIVISION_H
#define SUBDIVISION_H

#include "../../geometry/Rectangle.hpp"
#include <list>
#include "../cell/Cell.hpp"
#include "../cell/animalcell/AnimalCell.hpp"
#include "../cell/plantcell/PlantCell.hpp"

class Cell;

class Subdivision
{
    std::list<Cell*> containedCells;
    std::list<Cell*> nearbyCells;

    friend Cell;
    
  public:
    const Rectangle hitBox;
    
    Subdivision(int x, int y);
    Subdivision(const Subdivision&) = delete;
    Subdivision& operator=(const Subdivision&) = delete;
    ~Subdivision();

    const std::list<Cell*> getContainedCells() const;
    const std::list<Cell*> getNearbyCells() const;
};

#endif // SUBDIVISION_H