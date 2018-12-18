#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML/Graphics.hpp>

class Rectangle
{
  public:
    Rectangle(float x, float y, float width, float height);

    float x;
    float y;
    float width;
    float height;
    
    bool intersects(const Rectangle& rectangle) const;
};

#endif // RECTANGLE_H