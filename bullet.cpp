#include <ncurses.h>
#include "bullet.h"

Bullet::Bullet(Vec2 translation) : m_translation(translation) {}

void Bullet::render(WINDOW *wgame) const
{
    mvwprintw(wgame, m_translation.y + 1, 2 * m_translation.x + 2, "^");
}

void Bullet::move(Vec2 dr)
{
    m_translation = m_translation.add(dr);
}

Vec2 Bullet::translation() const
{
    return m_translation;
}
