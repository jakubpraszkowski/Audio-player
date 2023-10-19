#ifndef MUSICLIBRARY_USERINTERFACE_HPP
#define MUSICLIBRARY_USERINTERFACE_HPP

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include "Song.hpp"
#include <array>
#include <iostream>
#include <ncurses/ncurses.h>
#include <thread>

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

    const std::array<std::string, 7> defaultMenu = {
        "Play", "Pause", "Stop", "Next", "Previous", "Shuffle", "Exit"};

  public:
    static void changeDir(fs::path *nDirectory);
    void createWindow(MusicLibrary &ml, AudioPlayer &ap);

    void initWinParams(WIN *p_win);
    void printWinParams(WIN *p_win);
    void createBoxes(WIN *box1, WIN *box2, WIN *box3);
    void drawBorders(WIN &box);

    void printSongsInsideBox(
        MusicLibrary &ml, int startY, int startX, int height, int width,
        int &currentLine);
    void moveKeysScreen(
        MusicLibrary &ml, AudioPlayer &ap, WIN *win1, WIN *win2, WIN *win3,
        int &ch, WIN_BOX &winBox, std::thread &playbackThread);

    template <typename T>
    void moveDownVector(std::vector<T> &vec, int &currentLine);

    void printMenu(int &currentLine);
    void moveDown(int &currentLine);
    void moveUp(int &currentLine);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
