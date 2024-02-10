#pragma once

#include "vec2.h"

class Player
{
public:
    Player(int health, Vec2 translation);

    Vec2 translation() const;
    void render() const;
    void move(Vec2 dr, Vec2 min, Vec2 max);

private:
    int m_health;
    Vec2 m_translation;
};
