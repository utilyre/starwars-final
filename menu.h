#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

struct MenuItem {
    std::string name;
    void (*action)();

    MenuItem(std::string name, void (*action)());
};

class Menu
{
public:
    Menu(int width, std::vector<MenuItem> m_items);
    ~Menu();

    void start();

private:
    WINDOW *m_window;
    int m_width;
    std::size_t m_selected;
    std::vector<MenuItem> m_items;

    void render() const;
    bool input();
};
