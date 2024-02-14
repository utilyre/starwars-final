#pragma once

#include <ncurses.h>
#include "vec2.h"

class Player
{
public:
    Player(int health, Vec2 translation);

    void render(WINDOW *wgame) const;

    bool is_dead() const;
    Vec2 translation() const;

    void take_damage(int amount);
    void move(Vec2 dr, Vec2 min, Vec2 max);

private:
    int m_health;
    Vec2 m_translation;
};
