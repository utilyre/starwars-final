#include "startup-menu.h"

StartupMenu::StartupMenu() : m_selected(0), m_options({"Continue", "New Game", "Quit"})
{
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    m_window = newwin(2 * m_options.size() + 3, 20, (LINES - 2 * m_options.size() - 3) / 2, (COLS - 20) / 2);
    keypad(m_window, true);
    refresh();
}

StartupMenu::~StartupMenu()
{
    delwin(m_window);
}

void StartupMenu::start()
{
    while (true)
    {
        wclear(m_window);
        box(m_window, 0, 0);

        render();
        if (!input())
        {
            return;
        }
    }
}

void StartupMenu::render() const
{
    for (std::size_t i = 0; i < m_options.size(); i++)
    {
        const std::string &option = m_options[i];

        if (i == m_selected)
        {
            wattron(m_window, COLOR_PAIR(1));
        }

        mvwprintw(m_window, 2 * (i + 1), (18 - option.size()) / 2, " %s ", option.c_str());

        if (i == m_selected)
        {
            wattroff(m_window, COLOR_PAIR(1));
        }
    }
}

bool StartupMenu::input()
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
        if (m_selected < m_options.size() - 1)
        {
            m_selected++;
        }

        break;
    case ' ':
        switch (m_selected)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            return false;
        }

        break;
    }

    return true;
}
