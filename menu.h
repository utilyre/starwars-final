#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <functional>

class Menu;
class MenuItem;

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

struct MenuItem
{
    std::string name;
    std::function<void(Menu &)> action;

    MenuItem(std::string name, std::function<void(Menu &)>);
};
