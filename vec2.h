#pragma once

/**
 * Represents a vector on two-dimensional plane.
 */
struct Vec2
{
    int y, x;

    Vec2();
    Vec2(int y, int x);

    /**
     * Adds `other` to the vector.
     */
    Vec2 add(Vec2 other);

    /**
     * Clamps the vector between `min` and `max`.
     */
    Vec2 clamp(Vec2 min, Vec2 max);
};
