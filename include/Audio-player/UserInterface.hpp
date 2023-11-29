#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_USERINTERFACE_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_USERINTERFACE_HPP

#include <array>
#include <thread>

#include <ncurses/ncurses.h>

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include "Song.hpp"

class UserInterface {
  private:
    struct WIN_BOX;
    struct MENU_BOOL;

  public:
    static void entryPoint();

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

    void initNcurses();

    void processKeyUp(WIN_BOX &winBox);

    void processKeyDown(WIN_BOX &winBox, MusicLibrary &ml);

    void leftMenuAction(WIN_BOX &winBox, MusicLibrary &ml, AudioPlayer &ap);

    void whichVectorShow(
        WIN_BOX &winBox, MENU_BOOL &menuBool, MusicLibrary &ml,
        WINDOW *mainWin);

  private:
    struct WIN_BOX {
        int currentLine1stBox = 0;
        int currentLine3rdBox = 0;
        int currentBox = 2;
    };

    struct WINDOW_INIT {
        int mainWinWidth = 0;
        int mainWinHeight = 0;
        int sidebarWinWidth = 20;
        int sidebarWinX = 0;
        int sidebarWinY = 0;
        int topWinHeight = 5;
        int topWinY = 0;
        int mainWinY = 0;
        int mainWinX = 0;
    };

    struct MENU_BOOL {
        bool isSongMenu = false;
        bool isAlbumMenu = false;
        bool isPlaylistMenu = false;
    };

    typedef enum { PLAY, SONGS, ALBUMS, SHUFFLE } MENU;

    const std::array<std::string, 4> defaultMenu = {
        "Play", "Songs", "Albums", "Shuffle"};

    const std::array<std::string, 3> musicStatus = {
        "Playing", "Paused", "Empty queue"};
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
