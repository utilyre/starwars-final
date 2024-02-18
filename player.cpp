#include <ncurses.h>
#include <fstream>
#include "player.h"

Player::Player() : m_health(1), m_score(0), m_translation() {}
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

void Player::save_to(std::ofstream &out) const
{
    out.write(reinterpret_cast<const char *>(&m_health), sizeof(m_health));
    out.write(reinterpret_cast<const char *>(&m_score), sizeof(m_score));
    out.write(reinterpret_cast<const char *>(&m_translation), sizeof(m_translation));
}

void Player::load_from(std::ifstream &in)
{
    in.read(reinterpret_cast<char *>(&m_health), sizeof(m_health));
    in.read(reinterpret_cast<char *>(&m_score), sizeof(m_score));
    in.read(reinterpret_cast<char *>(&m_translation), sizeof(m_translation));
}

int Player::score() const
{
    return m_score;
}
