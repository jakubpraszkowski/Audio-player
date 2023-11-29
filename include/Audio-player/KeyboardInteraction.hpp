#ifndef KEYBOARDINTERACTION_HPP
#define KEYBOARDINTERACTION_HPP

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include <fstream>
#include <ncurses/ncurses.h>

#define KEY_TAB '\t'
#define KEY_PAUSE 'p'
#define MUSIC_MENU 1
#define LEFT_MENU 2

class KeyboardInteraction {
  protected:
    typedef struct _win_current_line {
        int currentLine1stBox = 0;
        int currentLine3rdBox = 0;
        int currentLineSongMenu = 0;
        int currentLineAlbumMenu = 0;
        int currentBox = 1;
    } WIN_BOX;

    typedef struct _menu_bool {
        bool songMenu = true;
        bool albumMenu = false;
        bool playlistMenu = false;
    } MENU_BOOL;

    typedef enum { PLAY, SONGS, ALBUMS } MENU;

  public:
    KeyboardInteraction(){};

    void moveOnScreen(
        MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &input,
        MENU_BOOL &menuBool);

    void musicMenu(
        MusicLibrary &ml, AudioPlayer &ap, MENU_BOOL &menuBool,
        WIN_BOX &winBox);

    void playQueue(AudioPlayer &ap, std::thread &playbackThread);

    void moveUp(int &currentLine);

    void
    moveDown(const std::array<std::string, 4> &arrayMenu, int &currentLine);

    template <typename T>
    void moveDown(const std::vector<T> &vec, int &currentLine) {
        if (currentLine < vec.size() - 1) {
            ++currentLine;
        }
    }

    int changeCurrentBox(WIN_BOX &winBox);

    void processKeyUp(WIN_BOX &winBox, MENU_BOOL &menuBool);
};
#endif // KEYBOARDINTERACTION_HPP