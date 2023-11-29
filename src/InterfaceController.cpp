#include "../include/Audio-player/InterfaceController.hpp"

void InterfaceController::createWindow(MusicLibrary &ml) {
    int input = 0;
    initWindowParams();
    WINDOW_INIT winInit;
    MENU_BOOL menuBool;
    WIN_BOX winBox;

    std::thread playbackThread;

    do {
        getmaxyx(stdscr, winInit.mainWinHeight, winInit.mainWinWidth);

        WINDOW *sidebarWin = newwin(
            winInit.mainWinHeight, winInit.sidebarWinWidth, winInit.sidebarWinY,
            winInit.sidebarWinX);
        WINDOW *topWin = newwin(
            winInit.topWinHeight,
            winInit.mainWinWidth - winInit.sidebarWinWidth, winInit.topWinY,
            winInit.sidebarWinWidth);
        WINDOW *mainWin = newwin(
            winInit.mainWinHeight - winInit.topWinHeight,
            winInit.mainWinWidth - winInit.sidebarWinWidth,
            winInit.topWinHeight, winInit.sidebarWinWidth);

        box(sidebarWin, 0, 0);
        box(topWin, 0, 0);
        box(mainWin, 0, 0);

        moveOnScreen(
            ml, apInstance, winBox, input, playbackThread, mainWin, topWin,
            sidebarWin);

        wrefresh(sidebarWin);
        wrefresh(topWin);
        wrefresh(mainWin);

    } while (input = getch() != KEY_F(1));

    if (playbackThread.joinable()) {
        playbackThread.join();
    }

    endwin();
    delwin(stdscr);
}

void InterfaceController::entryPoint() {
    FileManager fm;
    fm.scanDirectory();
    MusicLibrary ml;
    ml.updateSongs(fm);
    AudioPlayer ap;
    InterfaceController ic(UserInterface(), KeyboardInteraction(), ap);
    ic.createWindow(ml);
}

void InterfaceController::moveOnScreen(
    MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &ch,
    std::thread &playbackThread, WINDOW *mainWin, WINDOW *topWin,
    WINDOW *sidebarWin) {
    switch (ch) {
    case '\t':
        winBox.currentBox = (winBox.currentBox % 2) + 1;
        break;
    case KEY_UP:
        if (winBox.currentBox == 1) {
            moveUp(winBox.currentLine3rdBox);
        } else if (winBox.currentBox == 2) {
            moveUp(winBox.currentLine1stBox);
        }
        break;
    case KEY_DOWN:
        if (winBox.currentBox == 1) {
            moveDown(ml.getSongs(), winBox.currentLine3rdBox);
        } else if (winBox.currentBox == 2) {
            moveDown(getOptionMenu(), winBox.currentLine1stBox);
        }
        break;
    case KEY_F(4):
        if (winBox.currentBox == 1) {
            ap.loadSound2Queue(winBox.currentLine3rdBox, ml.getSongs());
        } else if (winBox.currentBox == 2 && winBox.currentLine1stBox == 0) {
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

    MENU_BOOL menuBool{true, false, false};

    if (winBox.currentLine1stBox == MENU::SONGS) {
        menuBool.songMenu = true;
        menuBool.albumMenu = false;
        menuBool.playlistMenu = false;

    } else if (winBox.currentLine1stBox == MENU::ALBUMS) {
        menuBool.songMenu = false;
        menuBool.albumMenu = true;
        menuBool.playlistMenu = false;
    }
    if (menuBool.songMenu && !menuBool.albumMenu && !menuBool.playlistMenu) {
        printVectorInsideBox(
            ml, mainWin, winBox.currentLine3rdBox, ml.getSongs());
    } else if (
        menuBool.albumMenu && !menuBool.songMenu && !menuBool.playlistMenu) {
        printVectorInsideBox(
            ml, mainWin, winBox.currentLine3rdBox, ml.getAlbums());
    }

    printMenu(winBox.currentLine1stBox);
}