#include "../include/Audio-player/KeyboardInteraction.hpp"

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