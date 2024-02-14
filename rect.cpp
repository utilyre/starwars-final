#include "rect.h"
#include "vec2.h"

Rect::Rect(Vec2 size, Vec2 translation) : size(size), translation(translation) {}
Rect::Rect(int height, int width, int y, int x) : size(height, width), translation(y, x) {}

int Rect::top() const
{
    return translation.y;
}

int Rect::left() const
{
    return translation.x;
}

int Rect::bottom() const
{
    return translation.y + size.y - 1;
}

int Rect::right() const
{
    return translation.x + size.x - 1;
}

bool Rect::collides_with(Rect other) const
{
    return top() <= other.bottom() && bottom() >= other.top() &&
           left() <= other.right() && right() >= other.left();
}
