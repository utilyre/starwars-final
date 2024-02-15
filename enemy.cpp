#include <ncurses.h>
#include <random>
#include "enemy.h"

Enemy::Enemy(int health, Vec2 size) : m_health(health), m_collision(size, Vec2()) {}

Enemy::Enemy(const Enemy &blueprint, int range) : m_health(blueprint.m_health), m_collision(blueprint.m_collision)
{
    m_collision.translation.x = rand() % (range - blueprint.m_collision.size.x + 1);
}

void Enemy::render(WINDOW *wgame) const
{
    for (int i = m_collision.top(); i <= m_collision.bottom(); i++)
    {
        for (int j = m_collision.left(); j <= m_collision.right(); j++)
        {
            mvwprintw(wgame, i + 1, 2 * j + 2, "*");
        }
    }
}

bool Enemy::collides_with(Rect other) const
{
    return m_collision.collides_with(other);
}

void Enemy::move(Vec2 dr)
{
    m_collision.translation = m_collision.translation.add(dr);
}

void Enemy::take_damage(int amount)
{
    m_health -= amount;
}

bool Enemy::is_dead() const
{
    return m_health <= 0;
}

int Enemy::points() const
{
    return 2 * m_collision.size.y * m_collision.size.x;
}
