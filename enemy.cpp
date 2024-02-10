#include <ncurses.h>
#include "enemy.h"

Enemy::Enemy(int health, Vec2 size, Vec2 translation) : m_health(health),
                                                        m_size(size),
                                                        m_translation(translation)
{
}

void Enemy::render() const
{
    for (int i = 0; i < m_size.y; i++)
    {
        for (int j = 0; j < m_size.x; j++)
        {
            mvprintw(m_translation.y + i, 2 * (m_translation.x + j) + 1, "*");
        }
    }
}

int Enemy::bottom() const
{
    return m_translation.y + m_size.y - 1;
}

void Enemy::move(Vec2 dr)
{
    m_translation = m_translation.add(dr);
}
