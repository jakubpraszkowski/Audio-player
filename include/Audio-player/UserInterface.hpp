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
        int currentLine1stBox = 0;
        int currentLine3rdBox = 0;
        int currentBox = 2;
    } WIN_BOX;

    typedef struct _window_init_params {
        int mainWinWidth = 0;
        int mainWinHeight = 0;
        int sidebarWinWidth = 20;
        int sidebarWinX = 0;
        int sidebarWinY = 0;
        int topWinHeight = 5;
        int topWinY = 0;
        int mainWinY = 0;
        int mainWinX = 0;
    } WINDOW_INIT;

    typedef enum { PLAY, SONGS, ALBUMS, SHUFFLE } MENU;

    const std::array<std::string, 7> defaultMenu = {
        "Play", "Songs", "Albums", "Shuffle"};

    const std::array<std::string, 3> musicStatus = {
        "Playing", "Paused", "Empty queue"};

    typedef struct _menu_bool {
        bool isSongMenu = false;
        bool isAlbumMenu = false;
        bool isPlaylistMenu = false;
    } MENU_BOOL;

  public:
    static void changeDir(fs::path nDirectory);

    void createWindow(MusicLibrary &ml, AudioPlayer &ap);

    void moveKeysScreen(
        MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &ch,
        std::thread &playbackThread, WINDOW *win, WINDOW *topWin,
        WINDOW *sidebarWin);

    template <typename T>
    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine, std::vector<T> &vec);

    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine,
        std::vector<Album> &vec);

    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
        std::vector<std::shared_ptr<Song>> &vec);

    template <typename T>
    void printMapInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine,
        const std::unordered_map<std::string, T> &map);

    template <typename T>
    void moveDownVector(std::vector<T> &vec, int &currentLine);

    void moveDownVector(
        const std::vector<std::shared_ptr<Song>> &vec, int &currentLine);

    void moveDown(int &currentLine);

    void moveUp(int &currentLine);

    void printMenu(int &currentLine);

    void printStatus(AudioPlayer &ap, WINDOW *topWin);

    void printProgressBar(AudioPlayer &ap, WINDOW *topWin);

    void printCurrentSong(AudioPlayer &ap, WINDOW *topWin);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
