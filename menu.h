#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

class Menu;

struct MenuItem {
    std::string name;
    void (*action)(Menu &menu);

    MenuItem(std::string name, void (*action)(Menu &menu));
};

class Menu
{
public:
    Menu(int width, std::string title, std::vector<MenuItem> m_items);
    ~Menu();

    void start();
    void stop();

private:
    WINDOW *m_window;
    int m_width;

    std::string m_title;
    std::size_t m_selected;
    std::vector<MenuItem> m_items;

    bool m_stopped;

    void render() const;
    bool input();
};
