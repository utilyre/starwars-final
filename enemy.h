#pragma once

#include "vec2.h"

class Enemy
{
public:
    Enemy(int health, Vec2 size, Vec2 translation);

    void render() const;
    int bottom() const;
    void move(Vec2 dr);

private:
    int m_health;
    Vec2 m_size;
    Vec2 m_translation;
};
