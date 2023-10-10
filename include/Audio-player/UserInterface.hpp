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

public: // static void printSortSongMenu();
    // static void printSortPlaylistMenu();
    // static void welcomeMessage();
    // static void clearScreen();
    // static void sortPlaylistMenu(MusicLibrary &ml);
    // static void sortSongMenu(MusicLibrary &ml);
    static void changeDir(fs::path *nDirectory);
    void createWindow(MusicLibrary &ml);

    void initWinParams(WIN *p_win);
    void printWinParams(WIN *p_win);
    void createBoxes(WIN *box1, WIN *box2, WIN *box3);
    void drawBorders(WIN &box);

    template <typename T>
    void printVectorInsideBox(std::vector<T> &vec, int startY, int startX, int height, int width);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
