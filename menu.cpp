#include <string>
#include <vector>
#include "menu.h"
#include "colors.h"
#include <functional>

MenuItem::MenuItem(std::string name, std::function<void(Menu &)> action) : name(name), action(action) {}

Menu::Menu(int width, std::string title, std::vector<MenuItem> items) : m_width(width), m_title(title), m_selected(0), m_items(items), m_stopped(false)
{
    m_window = newwin(2 * m_items.size() + 4, width, (LINES - 2 * m_items.size() - 4) / 2, (COLS - width) / 2);
    keypad(m_window, true);
    refresh();
}

Menu::~Menu()
{
    delwin(m_window);
}

void Menu::start()
{
    while (true)
    {
        if (m_stopped)
        {
            return;
        }

        render();
        if (!input())
        {
            return;
        }
    }
}

void Menu::stop()
{
    m_stopped = true;

    wclear(m_window);
    wrefresh(m_window);
}

void Menu::render() const
{
    wclear(m_window);
    box(m_window, 0, 0);

    wattron(m_window, A_BOLD);
    mvwprintw(m_window, 1, (m_width - m_title.size()) / 2, "%s", m_title.c_str());
    wattroff(m_window, A_BOLD);

    for (std::size_t i = 0; i < m_items.size(); i++)
    {
        const MenuItem &item = m_items[i];

        if (i == m_selected)
        {
            wattron(m_window, COLOR_PAIR(CP_SELECTED));
        }

        mvwprintw(m_window, 2 * i + 3, (m_width - item.name.size() - 2) / 2, " %s ", item.name.c_str());

        if (i == m_selected)
        {
            wattroff(m_window, COLOR_PAIR(CP_SELECTED));
        }
    }
}

bool Menu::input()
{
    switch (wgetch(m_window))
    {
    case KEY_UP:
        if (m_selected > 0)
        {
            m_selected--;
        }

        break;
    case KEY_DOWN:
        if (m_selected < m_items.size() - 1)
        {
            m_selected++;
        }

        break;
    case '\n':
        m_items[m_selected].action(*this);
        break;
    }

    return true;
}
