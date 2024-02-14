#pragma once

#include <ncurses.h>
#include "vec2.h"

class Player
{
public:
    Player(int size, int health, Vec2 translation);

    Vec2 translation() const;
    void render(WINDOW* wgame) const;
    void move(Vec2 dr, Vec2 min, Vec2 max);
    void take_damage();
    bool is_dead() const;

private:
    int m_size;
    int m_health;
    Vec2 m_translation;
};
