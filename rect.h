#pragma once

#include "vec2.h"

struct Rect
{
    Vec2 size;
    Vec2 translation;

    Rect(Vec2 size, Vec2 translation);
    Rect(int height, int width, int y, int x);

    int top() const;
    int left() const;
    int bottom() const;
    int right() const;
    bool collides_with(Rect rect) const;
};
