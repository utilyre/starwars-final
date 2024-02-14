#pragma once

#include <ncurses.h>
#include "vec2.h"

class Bullet
{
public:
    Bullet(Vec2 translation);

    void render(WINDOW *wgame) const;

    Vec2 translation() const;

    void move(Vec2 dr);

private:
    Vec2 m_translation;
};
