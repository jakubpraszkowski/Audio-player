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
        int currentLineSongMenu;
        int currentLineAlbumMenu;
        int currentBox;
    } WIN_BOX;

    typedef struct _window_init_params {
        int mainWinWidth, mainWinHeight;
        int sidebarWinWidth, topWinHeight;
        int mainWinX, mainWinY;
        int sidebarWinX, sidebarWinY;
        int topWinY;
    } WINDOW_INIT;

    typedef enum { PLAY, SONGS, ALBUMS } MENU;

    const std::array<std::string, 7> defaultMenu = {
        "Play", "Songs", "Albums", "Next", "Previous", "Shuffle", "Exit"};

    const std::array<std::string, 3> musicStatus = {
        "Playing", "Paused", "Empty queue"};

    typedef struct _menu_bool {
        bool isSongMenu = true;
        bool isAlbumMenu = false;
        bool isPlaylistMenu = false;
    } MENU_BOOL;

  public:
    static void changeDir(fs::path nDirectory); // Reimplement

    void createWindow(MusicLibrary &ml, AudioPlayer &ap);

    void moveKeysScreen(
        MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &ch,
        std::thread &playbackThread, WINDOW *win, WINDOW *topWin,
        WINDOW *sidebarWin);

    template <typename T>
    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine, std::vector<T> &vec);

    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
        std::vector<std::shared_ptr<Song>> &vec);

    template <typename T>
    void printMapInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine,
        const std::unordered_map<std::string, T> &map);

    template <typename T>
    void moveDownVector(const std::vector<T> &vec, int &currentLine);

    void moveDown(int &currentLine);

    void moveUp(int &currentLine);

    void printMenu(int &currentLine);

    void printStatus(AudioPlayer &ap, WINDOW *topWin);

    void printProgressBar(AudioPlayer &ap, WINDOW *topWin);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
