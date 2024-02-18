#pragma once

#include <ncurses.h>
#include <fstream>
#include "vec2.h"

class Player
{
public:
    Player();
    Player(int health, Vec2 translation);

    void save_to(std::ofstream &out) const;
    void load_from(std::ifstream &in);

    void render(WINDOW *wgame) const;

    bool is_dead() const;
    int health() const;
    int score() const;
    Vec2 translation() const;

    void take_damage(int amount);
    void take_score(int amount);
    void move(Vec2 dr, Vec2 min, Vec2 max);

private:
    int m_health;
    int m_score;
    Vec2 m_translation;
};
