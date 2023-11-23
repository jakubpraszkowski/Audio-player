#include "../include/Audio-player/KeyboardInteraction.hpp"

void KeyboardInteraction::moveOnScreen(
    MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &input) {
    switch (input) {
    case KEY_TAB:
        winBox.currentBox = checkCurrentBox(winBox);
        break;

    case KEY_UP:
        processKeyUp(winBox, menuBool);
        break;

    case KEY_DOWN:
        processKeyDown(winBox, menuBool);
        break;
    }
}

void KeyboardInteraction::usePlayer(
    MusicLibrary &ml, AudioPlayer &ap, int &input,
    std::thread &playbackThread) {
    switch (input) {
    case KEY_ENTER:

        break;

    case KEY_PAUSE:

        break;
    }
}

/*    case KEY_F(4):
        if (winBox.currentBox == 1) {
            if (menuBool.isSongMenu) {
                ap.loadSound2Queue(winBox.currentLineSongMenu,
ml.getSongs()); } else if (menuBool.isAlbumMenu) {
                ap.loadSound2Queue(winBox.currentLineAlbumMenu,
ml.getAlbums());
            }
        }

        if (winBox.currentBox == 2 && winBox.currentLine1stBox == 0) {
            if (!playbackThread.joinable()) {
                playbackThread = std::thread([&ap]() { ap.playQueue(); });
            }
        }
        break;
    case KEY_RIGHT:
        if (ap.checkMusicPlaying()) {
            ap.advanceForwardMusic(ap.getCurrentMusic());
        }
        break;
    case KEY_LEFT:
        if (ap.checkMusicPlaying()) {
            ap.advanceBackwardMusic(ap.getCurrentMusic());
        }
        break;
    case char('s'):
        if (ap.checkMusicPlaying()) {
            ap.stopMusic(ap.getCurrentMusic());
        }
        break;
    case char('p'):
        ap.pauseOrResumeMusic(ap.getCurrentMusic());
        break;
    }

    if (defaultMenu[winBox.currentLine1stBox] == "Songs") {
        menuBool.isSongMenu = true;
        menuBool.isAlbumMenu = false;
        menuBool.isPlaylistMenu = false;
    } else if (defaultMenu[winBox.currentLine1stBox] == "Albums") {
        menuBool.isSongMenu = false;
        menuBool.isAlbumMenu = true;
        menuBool.isPlaylistMenu = false;
    } else if (defaultMenu[winBox.currentLine1stBox] == "Playlists") {
        menuBool.isSongMenu = false;
        menuBool.isAlbumMenu = false;
        menuBool.isPlaylistMenu = true;
    }

    if (menuBool.isSongMenu && !menuBool.isAlbumMenu &&
        !menuBool.isPlaylistMenu) {
        printVectorInsideBox(
            ml, mainWin, winBox.currentLineSongMenu, ml.getSongs());
    } else if (
        menuBool.isAlbumMenu && !menuBool.isSongMenu &&
        !menuBool.isPlaylistMenu) {
        printVectorInsideBox(
            ml, mainWin, winBox.currentLineAlbumMenu, ml.getAlbums());
    }

    printMenu(winBox.currentLine1stBox);
}*/

void KeyboardInteraction::moveUp(int &currentLine) {
    if (currentLine > 0) {
        --currentLine;
    }
}

void KeyboardInteraction::moveDown(
    const std::initializer_list<std::string> &list, int &currentLine) {
    if (currentLine < list.size() - 1) {
        ++currentLine;
    }
}

template <typename T>
void KeyboardInteraction::moveDown(
    const std::vector<T> &vec, int &currentLine) {
    if (currentLine < vec.size() - 1) {
        ++currentLine;
    }
}

WIN_BOX KeyboardInteraction::checkCurrentBox(WIN_BOX &winBox) {
    return winBox.currentBox = (winBox.currentBox % 2) + 1;
}

void KeyboardInteraction::processKeyUp(
    const WIN_BOX &winBox, const MENU_BOOL &menuBool) {
    if (winBox.currentBox == 1 && menuBool.isSongMenu) {
        moveUp(winBox.currentLineSongMenu);
    } else if (winBox.currentBox == 1 && menuBool.isAlbumMenu) {
        moveUp(winBox.currentLineAlbumMenu);
    } else if (winBox.currentBox == 2) {
        moveUp(winBox.currentLine1stBox);
    }
}

void KeyboardInteraction::processKeyDown(
    const WIN_BOX &winBox, const MENU_BOOL &menuBool) {
    if (winBox.currentBox == 1 && menuBool.isSongMenu) {
        moveDown(ml.getSongs(), winBox.currentLineSongMenu);
    } else if (winBox.currentBox == 1 && menuBool.isAlbumMenu) {
        moveDown(ml.getAlbums(), winBox.currentLineAlbumMenu);
    } else if (winBox.currentBox == 2) {
        moveDown(defaultMenu, winBox.currentLine1stBox);
    }
}