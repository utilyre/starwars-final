#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <functional>

class Menu;
struct MenuItem;

/**
 * Terminal menu interface powered by `ncurses`.
 */
class Menu
{
public:
    Menu(int width, std::string title, std::vector<MenuItem> m_items);
    ~Menu();

    /**
     * Start displaying the menu.
     *
     * Note that this method is a blocking call.
     */
    void start();

    /**
     * Stops displaying the menu by interrupting its infinite loop.
     */
    void stop();

private:
    WINDOW *m_window;
    int m_width;

    std::string m_title;
    std::size_t m_selected;
    std::vector<MenuItem> m_items;

    bool m_stopped;

    /**
     * Renders the menu based off of its state.
     */
    void render() const;

    /**
     * Waits for user interaction and handles it.
     */
    bool input();
};

/**
 * A `MenuItem` is used to pair a name with an action.
 */
struct MenuItem
{
    std::string name;
    std::function<void(Menu &)> action;

    MenuItem(std::string name, std::function<void(Menu &)>);
};
