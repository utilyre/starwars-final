#pragma once

#include "vec2.h"

/**
 * Represents a rectangle on a two-dimensional plane.
 */
struct Rect
{
    /**
     * Size of the rectangle.
     */
    Vec2 size;

    /**
     * Translation of the upper-left corner of the rectangle.
     */
    Vec2 translation;

    Rect();
    Rect(Vec2 size, Vec2 translation);
    Rect(int height, int width, int y, int x);

    /**
     * Returns the y-axis translation of the top edge.
     */
    int top() const;

    /**
     * Returns the x-axis translation of the left edge.
     */
    int left() const;

    /**
     * Returns the y-axis translation of the bottom edge.
     */
    int bottom() const;

    /**
     * Returns the x-axis translation of the right edge.
     */
    int right() const;

    /**
     * Checks whether this rectangle collides with `rect`.
     */
    bool collides_with(Rect rect) const;
};
