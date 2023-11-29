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
  protected:
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

  private:
    static const std::array<std::string, 4> optionMenu;

  public:
    static void changeDir(fs::path nDirectory); // Reimplement

    static const std::array<std::string, 4> &getOptionMenu();

    template <typename T>
    static void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine, std::vector<T> &vec);

    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
        std::vector<std::shared_ptr<Song>> &vec);

    void printVectorInsideBox(
        MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
        std::vector<Album> &vec);

    template <typename T>
    void printMapInsideBox(
        MusicLibrary &ml, WINDOW *win, int &currentLine,
        const std::unordered_map<std::string, T> &map);

    void printMenu(int &currentLine);

    void printProgressBar(AudioPlayer &ap, WINDOW *topWin);

    void initWindowParams();

    void createProgressBar(AudioPlayer &ap, WINDOW *win);

    void printCurrentSong(AudioPlayer &ap, WINDOW *win);
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
