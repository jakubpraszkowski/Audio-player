#ifndef MUSICLIBRARY_USERINTERFACE_HPP
#define MUSICLIBRARY_USERINTERFACE_HPP

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include "Song.hpp"
#include <array>
#include <iomanip>
#include <iostream>
#include <ncurses/ncurses.h>
#include <thread>

class UserInterface {
    typedef struct _win_current_struct {
        int currentLine1stBox;
        int currentLine3rdBox;
        int currentBox;
    } WIN_BOX;

    typedef struct _window_init_params {
        int mainWinWidth, mainWinHeight;
        int sidebarWinWidth, topWinHeight;
        int mainWinX, mainWinY;
        int sidebarWinX, sidebarWinY;
        int topWinY;
    } WINDOW_INIT;

    enum MENU { PLAY, SONGS, ALBUMS }; // TODO implement

    const std::array<std::string, 7> defaultMenu = {
        "Play", "Songs", "Albums", "Next", "Previous", "Shuffle", "Exit"};

    const std::array<std::string, 3> musicStatus = {
        "Playing", "Paused", "Empty queue"};

    bool isSongMenu = true, isAlbumMenu = false;

  public:
    static void changeDir(fs::path *nDirectory);
    void createWindow(MusicLibrary &ml, AudioPlayer &ap);

    template <typename T>
    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine, std::vector<T> &vec);

    void moveKeysScreen(
        MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &ch,
        std::thread &playbackThread, WINDOW *win, WINDOW *topWin,
        WINDOW *sidebarWin);

    template <typename T>
    void moveDownVector(std::vector<T> &vec, int &currentLine);

    void printMenu(int &currentLine);
    void moveDown(int &currentLine);
    void moveUp(int &currentLine);
    void printStatus(AudioPlayer &ap, WINDOW *topWin);
    void printProgressBar(AudioPlayer &ap, WINDOW *topWin);
    void printAlbumsInsideBox(
        MusicLibrary &ml, int startY, int startX, int height, int width,
        int &currentLine);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
