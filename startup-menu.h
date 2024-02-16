#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

class StartupMenu
{
public:
    StartupMenu();
    ~StartupMenu();

    void start();

private:
    WINDOW *m_window;
    std::size_t m_selected;
    std::vector<std::string> m_options;

    void render() const;
    bool input();
};
