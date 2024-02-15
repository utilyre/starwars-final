#pragma once

#include <ncurses.h>
#include <fstream>
#include "vec2.h"

class Bullet
{
public:
    Bullet(Vec2 translation);

    void save_to(std::ofstream &out) const;

    void render(WINDOW *wgame) const;

    Vec2 translation() const;

    void move(Vec2 dr);

private:
    Vec2 m_translation;
};
