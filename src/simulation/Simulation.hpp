#ifndef SIMULATION_H
#define SIMULATION_H

#include "cell/Cell.hpp"
#include <list>
#include <SFML/Graphics.hpp>
#include <vector>

class Cell;
class Subdivision;

class Simulation : sf::Drawable
{
    std::list<Cell*> cells;
    std::vector<Subdivision*> subdivisions;

    float scale;

    friend Cell;

  public:
    const sf::Vector2u dimensions;

    Simulation(sf::Vector2u dimensions);
    Simulation(const Simulation&) = delete;
    Simulation& operator=(const Simulation&) = delete;
    ~Simulation();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void completeTurns();

    ///////////////////////////
    // GETTERS AND SETTERS
    ///////////////////////////

    Subdivision& subdivisionAt(int x, int y) const;

    const std::list<Cell*> getAllCells() const;

    float getScale() const;
    void setScale(float value);
};

#endif // SIMULATION_H