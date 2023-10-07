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
    void createWindow();

    void init_win_params(WIN *p_win);
    void print_win_params(WIN *p_win);
    void create_boxes(WIN *box1, WIN *box2, WIN *box3);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
