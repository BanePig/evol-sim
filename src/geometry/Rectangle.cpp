#include "Rectangle.hpp"

Rectangle::Rectangle(float xOrigin, float yOrigin, float width, float height)
    : x(xOrigin), y(yOrigin), width(width), height(height)
{
}

bool Rectangle::intersects(const Rectangle& rectangle) const
{
    auto& left = x;
    auto right = x + width;
    auto& top = y;
    auto bottom = y + height;
    auto& rectLeft = rectangle.x;
    auto rectRight = rectangle.x + rectangle.width;
    auto& rectTop = rectangle.y;
    auto rectBottom = rectangle.y + rectangle.height;
    return (left < rectRight &&
        right > rectLeft &&
        top < rectBottom &&
        bottom > rectTop);
}