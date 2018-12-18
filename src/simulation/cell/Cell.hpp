#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "../../geometry/Rectangle.hpp"
#include "CellType.hpp"
#include <list>

class Simulation;
class Subdivision;

class Cell : public sf::Drawable
{
    sf::Vector2f position;
    Subdivision* containingSubdivision;
    std::list<Subdivision*> nearbySubdivisions;

  protected:
    const sf::Color color;
    float health;
    float size;

    Rectangle hitBox;

    void updateNearbySubdivisions();
    void updateContainingSubdivision();

  public:
    const CellType type;
    Simulation& parentSimulation;

    Cell(CellType type, Simulation& parentSimulation, const sf::Vector2f& position, const sf::Color& color, float size);
    Cell(const Cell&) = delete;
    Cell& operator=(const Cell&) = delete;
    virtual ~Cell();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void completeTurn() = 0;

    const sf::Color& getColor() const;
    float getHealth() const;
    float getSize() const;
    const Rectangle& getHitBox() const;
    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& pos);
};

#endif // CELL_H