#include <ncurses.h>
#include "player.h"

Player::Player(int health, Vec2 translation) : m_health(health), m_translation(translation) {}

Vec2 Player::translation() const
{
    return m_translation;
}

void Player::render() const
{
    mvprintw(m_translation.y, 2 * m_translation.x + 1, "#");
}

void Player::move(Vec2 dr, Vec2 min, Vec2 max)
{
    m_translation = m_translation
                        .add(dr)
                        .clamp(min, max);
}
