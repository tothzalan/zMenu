#include <ncurses.h>
#include <string>
#include <iostream>
#include <vector>
#include "config.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments!" << std::endl;
        return 0;
    }
    std::string path(argv[1]);
    std::vector<ItemModel> list = ReadInConfig(path);
    WINDOW *w;
    char item[list.size()];
    int ch, i = 0;
    bool canbreak = false;

    initscr();

    int x, y;
    getmaxyx(stdscr, x, y);

    w = newwin(x - 1, y - 1, 1, 1);
    box(w, 0, 0);

    for (i = 0; i < list.size(); i++)
    {
        if (i == 0)
            wattron(w, A_STANDOUT);
        else
            wattroff(w, A_STANDOUT);
        sprintf(item, "%s", list[i].Name.c_str());
        mvwprintw(w, i + 1, 2, "%s", item);
    }

    wrefresh(w);

    i = 0;
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    while ((ch = wgetch(w)) != 'q' && !canbreak)
    {

        sprintf(item, "%s", list[i].Name.c_str());
        mvwprintw(w, i + 1, 2, "%s", item);
        switch (ch)
        {
        case KEY_UP:
            i--;
            i = (i < 0) ? list.size() - 1 : i;
            break;
        case KEY_DOWN:
            i++;
            i = (i > list.size() - 1) ? 0 : i;
            break;
        case KEY_RIGHT:
            canbreak = true;
            break;
        }
        wattron(w, A_STANDOUT);

        sprintf(item, "%s", list[i].Name.c_str());
        mvwprintw(w, i + 1, 2, "%s", item);

        wattroff(w, A_STANDOUT);
    }
    delwin(w);
    endwin();
    system(list[i].Executable.c_str());
}