#include <ncurses.h>
#include "player.h"

Player::Player(int health, Vec2 translation) : m_health(health), m_score(0), m_translation(translation) {}

Vec2 Player::translation() const
{
    return m_translation;
}

void Player::render(WINDOW *wstatus, WINDOW *wgame) const
{
    mvwprintw(wstatus, 1, 1, "health: %d  score: %d", m_health, m_score);
    mvwprintw(wgame, m_translation.y + 1, 2 * m_translation.x + 2, "#");
}

void Player::move(Vec2 dr, Vec2 min, Vec2 max)
{
    m_translation = m_translation.add(dr).clamp(min, max);
}

void Player::take_damage(int amount)
{
    m_health -= amount;
}

bool Player::is_dead() const
{
    return m_health <= 0;
}

void Player::take_score(int amount)
{
    m_score += amount;
}
