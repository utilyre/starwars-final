#include <ncurses.h>
#include "player.h"

Player::Player(int size, int health, Vec2 translation) : m_size(size), m_health(health), m_translation(translation) {}

Vec2 Player::translation() const
{
    return m_translation;
}

void Player::render(WINDOW *wgame) const
{
    mvwprintw(wgame, m_translation.y+1, 2 * m_translation.x + 2, "#");
    // mvwprintw(wgame, 2, 2 * m_size + 2, "health: %d", m_health);
}

void Player::move(Vec2 dr, Vec2 min, Vec2 max)
{
    m_translation = m_translation
                        .add(dr)
                        .clamp(min, max);
}

void Player::take_damage()
{
    m_health--;
}

bool Player::is_dead() const
{
    return m_health <= 0;
}
