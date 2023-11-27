#include "../include/Audio-player/KeyboardInteraction.hpp"

void KeyboardInteraction::moveOnScreen(
    MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &input,
    MENU_BOOL &menuBool) {
    switch (input) {
    case KEY_TAB:
        winBox.currentBox = changeCurrentBox(winBox);
        break;

    case KEY_UP:
        processKeyUp(winBox, menuBool);
        break;

    case KEY_DOWN:
        processKeyDown(ml, winBox, menuBool);
        break;

    case KEY_ENTER:
        if (winBox.currentBox == MUSIC_MENU) {
            musicMenu(ml, ap, menuBool, winBox);
        } else if (winBox.currentBox == LEFT_MENU) {
            if (winBox.currentLine1stBox == 0) {
                std::thread playbackThread;
                playQueue(ap, playbackThread);
            }
        }
        break;

    case KEY_PAUSE:
        ap.pauseOrResumeMusic(ap.getCurrentMusic());
        break;

    case KEY_LEFT:
        ap.advanceForwardMusic(ap.getCurrentMusic());
        break;

    case KEY_RIGHT:
        ap.advanceBackwardMusic(ap.getCurrentMusic());
        break;
    }
}

void KeyboardInteraction::musicMenu(
    MusicLibrary &ml, AudioPlayer &ap, MENU_BOOL &menuBool, WIN_BOX &winBox) {
    if (menuBool.songMenu) {
        ap.loadSound2Queue(winBox.currentLineSongMenu, ml.getSongs());
    } else if (menuBool.albumMenu) {
        ap.loadSound2Queue(winBox.currentLineAlbumMenu, ml.getAlbums());
    }
}

void KeyboardInteraction::playQueue(
    AudioPlayer &ap, std::thread &playbackThread) {
    if (!playbackThread.joinable()) {
        playbackThread = std::thread([&ap]() { ap.playQueue(); });
    }
}

void KeyboardInteraction::moveUp(int &currentLine) {
    if (currentLine > 0) {
        --currentLine;
    }
}

void KeyboardInteraction::moveDown(
    const std::array<std::string, 4> &arrayMenu, int &currentLine) {
    if (currentLine < 4 - 1) {
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

int KeyboardInteraction::changeCurrentBox(WIN_BOX &winBox) {
    return winBox.currentBox = (winBox.currentBox % 2) + 1;
}

void KeyboardInteraction::processKeyUp(WIN_BOX &winBox, MENU_BOOL &menuBool) {
    if (winBox.currentBox == MUSIC_MENU && menuBool.songMenu) {
        moveUp(winBox.currentLineSongMenu);
    } else if (winBox.currentBox == MUSIC_MENU && menuBool.albumMenu) {
        moveUp(winBox.currentLineAlbumMenu);
    } else if (winBox.currentBox == LEFT_MENU) {
        moveUp(winBox.currentLine1stBox);
    }
}

void KeyboardInteraction::processKeyDown(
    MusicLibrary &ml, WIN_BOX &winBox, MENU_BOOL &menuBool) {
    if (winBox.currentBox == MUSIC_MENU && menuBool.songMenu) {
        moveDown(ml.getSongs(), winBox.currentLineSongMenu);
    } else if (winBox.currentBox == MUSIC_MENU && menuBool.albumMenu) {
        moveDown(ml.getAlbums(), winBox.currentLineAlbumMenu);
    } else if (winBox.currentBox == LEFT_MENU) {
        moveDown(UserInterface().getOptionMenu(), winBox.currentLine1stBox);
    }
}