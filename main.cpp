#include <ncurses.h>
#include <time.h>
#include <random>
#include "colors.h"
#include "menu.h"
#include "game.h"
#include "utils.h"
#include "rect.h"
#include <string.h>
#include <fstream>

/**
 * Initialize libraries.
 */
void init();

/**
 * Open the main menu.
 */
void open_menu();

int main()
{
    init();
    open_menu();
    endwin();
}

void init()
{
    srand(time(0));

    initscr();
    start_color();
    noecho();
    curs_set(0);

    init_pair(CP_PLAYER, COLOR_BLUE, COLOR_BLACK);
    init_pair(CP_BULLET, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_ENEMY, COLOR_RED, COLOR_BLACK);
    init_pair(CP_SELECTED, COLOR_BLACK, COLOR_WHITE);
}

void open_menu()
{
    Menu menu(
        25,
        "StarWars",
        {
            MenuItem("Continue", [](Menu &menu)
                     {
                        std::ifstream f("state.dat");
                        if (!f.is_open())
                        {
                            return;
                        }
                        f.close();

                        menu.stop();

                        Game game;
                        game.start(); }),

            MenuItem("New Game", [](Menu &menu)
                     {
                        int size;
                        do
                        {
                            char size_str[3];
                            ninput(" Size: ", Rect(3, 48, (LINES - 3) / 2, (COLS - 48) / 2), 2, size_str);
                            size = std::atoi(size_str);
                        } while (size < 15 || size >= LINES - 7 || size >= COLS - 4);

                        int max_score;
                        do
                        {
                            char max_score_str[5];
                            ninput(" Max Score: ", Rect(3, 48, (LINES - 3) / 2, (COLS - 48) / 2), 4, max_score_str);
                            max_score = std::atoi(max_score_str);
                        } while (max_score <= 0);

                        menu.stop();
                        Game game(size, max_score);
                        game.start(); }),

            MenuItem("Quit", [](Menu &menu)
                     {
                        endwin();
                        exit(0); }),
        });

    menu.start();
}
