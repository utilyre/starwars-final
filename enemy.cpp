#include <ncurses.h>
#include <random>
#include "enemy.h"
#include "colorpairs.h"

Enemy::Enemy(int health, Vec2 size) : m_health(health), m_size(size) {}

Enemy::Enemy(const Enemy &blueprint, int range) : m_health(blueprint.m_health), m_size(blueprint.m_size)
{
    m_translation.x = rand() % (range - m_size.x + 1);
}

void Enemy::render(WINDOW *wgame) const
{
    for (int i = 0; i < m_size.y; i++)
    {
        for (int j = 0; j < m_size.x; j++)
        {
            wattron(wgame, COLOR_PAIR(CP_ENEMY));
            mvwprintw(wgame, m_translation.y + i + 1, 2 * (m_translation.x + j) + 2, "*");
            wattroff(wgame, COLOR_PAIR(CP_ENEMY));
        }
    }
}

int Enemy::left() const
{
    return m_translation.x;
}

int Enemy::top() const
{
    return m_translation.y;
}

int Enemy::right() const
{
    return m_translation.x + m_size.x - 1;
}

int Enemy::bottom() const
{
    return m_translation.y + m_size.y - 1;
}

void Enemy::move(Vec2 dr)
{
    m_translation = m_translation.add(dr);
}

void Enemy::take_damage(int amount)
{
    m_health -= amount;
}

bool Enemy::is_dead() const
{
    return m_health <= 0;
}

bool Enemy::collides_with(Vec2 translation) const
{
    return translation.y >= top() && translation.y <= bottom() &&
           translation.x >= left() && translation.x <= right();
}

int Enemy::points() const
{
    return 2 * m_size.y * m_size.x;
}
