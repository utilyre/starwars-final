#include <ncurses.h>
#include "player.h"
#include "colorpairs.h"

Player::Player(int health, Vec2 translation) : m_health(health), m_translation(translation) {}

Vec2 Player::translation() const
{
    return m_translation;
}

void Player::render(WINDOW *wgame) const
{
    wattron(wgame, COLOR_PAIR(CP_PLAYER));
    mvwprintw(wgame, m_translation.y + 1, 2 * m_translation.x + 2, "#");
    wattroff(wgame, COLOR_PAIR(CP_PLAYER));
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
