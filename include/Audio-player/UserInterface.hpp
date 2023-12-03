#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_USERINTERFACE_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_USERINTERFACE_HPP

#include <unistd.h>

#include <array>
#include <memory>
#include <thread>
#include <vector>

#include <ncurses/ncurses.h>

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include "Playlist.hpp"
#include "Song.hpp"

class UserInterface {
  private:
    struct WIN_BOX;
    struct MENU_BOOL;
    enum class MENU;

  public:
    static void entryPoint();

    void drawWindowsOnScreen(MusicLibrary &ml, AudioPlayer &ap);

    void moveOnScreenWithKeys(
        MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &ch,
        std::thread &playbackThread, WINDOW *win, WINDOW *topWin,
        WINDOW *sidebarWin);

    void printVectorInsideWindow(
        MusicLibrary &ml, WINDOW *win, int &currentLine,
        std::vector<Album> &vec);

    void printVectorInsideWindow(
        MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
        std::vector<std::shared_ptr<Song>> &vec);

    void printVectorInsideWindow(
        MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
        std::vector<Playlist> &vec);

    template <typename T> void moveDown(std::vector<T> &vec, int &currentLine);

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
        WIN_BOX &winBox, MENU_BOOL &menuBool, MusicLibrary &ml, WINDOW *mainWin,
        WINDOW *topWin);

    void updateUI(AudioPlayer &ap, WINDOW *topWin);

    void statusThread(AudioPlayer &ap, WINDOW *topWin);

    void createPlaylistMenu(WINDOW *topWin, int &ch, MusicLibrary &ml);

    std::string getMenuOption(MENU menu);

    void noPlaylists(WINDOW *mainWin);

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
        bool isCreatingPlaylist = false;
    };

    enum class MENU {
        PLAY,
        SONGS,
        ALBUMS,
        SHUFFLE,
        PLAYLISTS,
        CREATE_PLAYLIST,
        MENU_SIZE
    };

    const std::array<std::string, 3> musicStatus = {
        "Playing", "Paused", "Empty queue"};
};

#endif // MUSICLIBRARY_USERINTERFACE_HPP
