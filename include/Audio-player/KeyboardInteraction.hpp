#ifndef KEYBOARDINTERACTION_HPP
#define KEYBOARDINTERACTION_HPP

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include "UserInterface.hpp"
#include <ncurses/ncurses.h>

#define KEY_TAB '\t'
#define KEY_PAUSE 'p'
#define MUSIC_MENU 1
#define LEFT_MENU 2

// class UserInterface;

class KeyboardInteraction {

  public:
    KeyboardInteraction(){};

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
    void moveDown(const std::vector<T> &vec, int &currentLine);

    int changeCurrentBox(WIN_BOX &winBox);

    void processKeyUp(WIN_BOX &winBox, MENU_BOOL &menuBool);

    void processKeyDown(MusicLibrary &ml, WIN_BOX &winBox, MENU_BOOL &menuBool);

};     // TODO move UserInteface keyboard actions to this class
#endif // KEYBOARDINTERACTION_HPP