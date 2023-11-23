#pragma once
#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include <ncurses/ncurses.h>

#define KEY_TAB '\t'
#define KEY_PAUSE 'p'

class KeyboardInteraction {

  public:
    KeyboardInteraction() = default;
    ~KeyboardInteraction();

    typedef struct _win_current_line {
        int currentLine1stBox = 0;
        int currentLineSongMenu = 0;
        int currentLineAlbumMenu = 0;
        int currentBox = 1;
    } WIN_BOX;

    typedef struct _menu_bool {
        bool songMenu = 1;
        bool albumMenu = 0;
        bool playlistMenu = 0;
    } MENU_BOOL;

    void moveOnScreen(
        MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &input);

    void usePlayer(
        MusicLibrary &ml, AudioPlayer &ap, int &input,
        std::thread &playbackThread);

    void moveUp(int &currentLine);

    void
    moveDown(const std::initializer_list<std::string> &list, int &currentLine);

    template <typename T>
    void moveDown(const std::vector<T> &vec, int &currentLine);

    WIN_BOX checkCurrentBox(WIN_BOX &winBox);

    void processKeyUp(const WIN_BOX &winBox, const MENU_BOOL &menuBool);

    void processKeyDown(const WIN_BOX &winBox, const MENU_BOOL &menuBool);

}; // TODO move UserInteface keyboard actions to this class