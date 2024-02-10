#pragma once

struct Vec2
{
    int y, x;

    Vec2();
    Vec2(int y, int x);

    Vec2 add(Vec2 other);
    Vec2 clamp(Vec2 min, Vec2 max);
};
