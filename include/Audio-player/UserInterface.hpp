#ifndef MUSICLIBRARY_USERINTERFACE_HPP
#define MUSICLIBRARY_USERINTERFACE_HPP

#include "MusicLibrary.hpp"
#include "Song.hpp"
#include <csignal>
#include <iostream>
#include <ncurses/ncurses.h>

class UserInterface {
    typedef struct _win_border_struct {
        chtype ls, rs, ts, bs, tl, tr, bl, br;
    } WIN_BORDER;

    typedef struct _WIN_struct {
        int startx, starty;
        int height, width;
        WIN_BORDER border;
    } WIN;

    typedef struct _win_current_struct {
        int currentLine1stBox;
        int currentLine3rdBox;
        int currentBox;
    } WIN_BOX;

    static const std::string defaultMenu[];

  public:
    static void changeDir(fs::path *nDirectory);
    void createWindow(MusicLibrary &ml);

    void initWinParams(WIN *p_win);
    void printWinParams(WIN *p_win);
    void createBoxes(WIN *box1, WIN *box2, WIN *box3);
    void drawBorders(WIN &box);

    void printSongsInsideBox(
        MusicLibrary &ml, int startY, int startX, int height, int width,
        int &currentLine);
    void moveKeysScreen(
        MusicLibrary &ml, WIN *win1, WIN *win2, WIN *win3, int &ch,
        WIN_BOX &winBox);

    template <typename T>
    void moveUpVector(std::vector<T> &vec, int &currentLine);

    template <typename T>
    void moveDownVector(std::vector<T> &vec, int &currentLine);

    void printMenu(int &currentLine);
    void moveDown(int &currentLine);
    void moveUp(int &currentLine);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
