#ifndef MUSICLIBRARY_USERINTERFACE_HPP
#define MUSICLIBRARY_USERINTERFACE_HPP

#include <iostream>
#include <ncurses/ncurses.h>
#include "MusicLibrary.hpp"
#include "Song.hpp"

class UserInterface
{
    typedef struct _win_border_struct
    {
        chtype ls, rs, ts, bs,
            tl, tr, bl, br;
    } WIN_BORDER;

    typedef struct _WIN_struct
    {
        int startx, starty;
        int height, width;
        WIN_BORDER border;
    } WIN;

    int currentLine;
    static const std::string defaultMenu[];

public:
    UserInterface(int currentLine = 0) : currentLine(currentLine) {};
    static void changeDir(fs::path *nDirectory);
    void createWindow(MusicLibrary &ml);

    void initWinParams(WIN *p_win);
    void printWinParams(WIN *p_win);
    void createBoxes(WIN *box1, WIN *box2, WIN *box3);
    void drawBorders(WIN &box);

    void printSongsInsideBox(MusicLibrary &ml, int startY, int startX, int height, int width);
    void moveKeysScreen(MusicLibrary &ml, int &startY, int &startX, int &height, int &width, int &ch);

    template <typename T>
    void moveUpVector(std::vector<T> &vec);

    template <typename T>
    void moveDownVector(std::vector<T> &vec);

    void printMenu();
    void moveDownMenu();
    void moveUpMenu();
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
