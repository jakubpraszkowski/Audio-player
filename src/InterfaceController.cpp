#include "../include/Audio-player/InterfaceController.hpp"

void InterfaceController::createWindow(MusicLibrary &ml) {
    int input = 0;
    initWindowParams();
    WINDOW_INIT winInit;
    MENU_BOOL menuBool;
    WIN_BOX winBox;

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

        printMenu(winBox.currentLine1stBox);
        moveOnScreen(ml, apInstance, winBox, input, menuBool);
        printVectorInsideBox(
            ml, mainWin, winBox.currentLineSongMenu, ml.getSongs());

        wrefresh(sidebarWin);
        wrefresh(topWin);
        wrefresh(mainWin);

    } while (input = getch() != KEY_F(1));

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

void InterfaceController::processKeyDown(
    MusicLibrary &ml, WIN_BOX &winBox, MENU_BOOL &menuBool) {
    if (winBox.currentBox == MUSIC_MENU && menuBool.songMenu) {
        moveDown(ml.getSongs(), winBox.currentLineSongMenu);
    } else if (winBox.currentBox == MUSIC_MENU && menuBool.albumMenu) {
        moveDown(ml.getAlbums(), winBox.currentLineAlbumMenu);
    } else if (winBox.currentBox == LEFT_MENU) {
        moveDown(getOptionMenu(), winBox.currentLine1stBox);
    }
}

void InterfaceController::moveOnScreen(
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