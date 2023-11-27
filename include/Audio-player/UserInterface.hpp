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

class KeyboardInteraction;

class UserInterface {
    typedef struct _window_init_params {
        int mainWinWidth = 0;
        int mainWinHeight = 0;
        int sidebarWinWidth = 20;
        int topWinHeight = 5;
        int mainWinX = 0;
        int mainWinY = 0;
        int sidebarWinX = 0;
        int sidebarWinY = 0;
        int topWinY = 0;
    } WINDOW_INIT;

    static const std::array<std::string, 4> optionMenu;

    typedef struct _menu_bool {
        bool isSongMenu = true;
        bool isAlbumMenu = false;
        bool isPlaylistMenu = false;
    } MENU_BOOL;

  public:
    static void changeDir(fs::path nDirectory); // Reimplement

    static const std::array<std::string, 4> &getOptionMenu();

    void createWindow(MusicLibrary &ml, AudioPlayer ap, KeyboardInteraction ki);

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

    void printProgressBar(AudioPlayer &ap, WINDOW *topWin);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
