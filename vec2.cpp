#include <algorithm>
#include "vec2.h"

Vec2::Vec2() : y(0), x(0) {}
Vec2::Vec2(int y, int x) : y(y), x(x) {}

Vec2 Vec2::add(Vec2 other)
{
    return Vec2(y + other.y, x + other.x);
}

Vec2 Vec2::clamp(Vec2 min, Vec2 max)
{
    return Vec2(std::clamp(y, min.y, max.y), std::clamp(x, min.x, max.x));
}
