#include "../include/Audio-player/UserInterface.hpp"

void UserInterface::entryPoint() {
    FileManager fm;
    fm.scanDirectory();
    MusicLibrary ml;
    ml.updateSongs(fm);
    UserInterface ui;
    AudioPlayer ap;
    ui.createWindow(ml, ap);
}

void UserInterface::changeDir(fs::path nDirectory) {
    std::cout << "Where to look for songs? Please provide the full path: ";
    std::cin >> nDirectory;
}

void UserInterface::createWindow(MusicLibrary &ml, AudioPlayer &ap) {
    int ch;
    initNcurses();
    std::thread playbackThread;
    WINDOW_INIT winInit;
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

        moveKeysScreen(
            ml, ap, winBox, ch, playbackThread, mainWin, topWin, sidebarWin);
        printCurrentSong(ap, topWin);

        wrefresh(sidebarWin);
        wrefresh(topWin);
        wrefresh(mainWin);

    } while ((ch = getch()) != KEY_F(1));

    if (playbackThread.joinable())
        playbackThread.join();

    endwin();
    delwin(stdscr);
}

void UserInterface::moveKeysScreen(
    MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &ch,
    std::thread &playbackThread, WINDOW *mainWin, WINDOW *topWin,
    WINDOW *sidebarWin) {
    switch (ch) {
    case '\t':
        winBox.currentBox = (winBox.currentBox % 2) + 1;
        break;

    case KEY_UP:
        processKeyUp(winBox);
        break;

    case KEY_DOWN:
        processKeyDown(winBox, ml);
        break;

    case KEY_F(4):
        if (winBox.currentBox == 1) {
            leftMenuAction(winBox, ml, ap);
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

    default:
        break;
    }

    MENU_BOOL menuBool;
    whichVectorShow(winBox, menuBool, ml, mainWin);
}

void UserInterface::printVectorInsideBox(
    MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
    std::vector<Album> &vec) {

    int maxLines = mainWin->_maxy - 2;

    if (currentLine < 0)
        currentLine = 0;
    if (currentLine >= vec.size())
        currentLine = vec.size() - 1;

    int startIdx = currentLine;
    int endIdx =
        std::min(currentLine + maxLines, static_cast<int>(vec.size()) - 1);

    for (int i = startIdx; i <= endIdx; i++) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                vec[i].getAlbumName().c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                vec[i].getAlbumName().c_str());
        }
    }
}

void UserInterface::printVectorInsideBox(
    MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
    std::vector<std::shared_ptr<Song>> &vec) {
    int maxLines = mainWin->_maxy - 2;

    if (currentLine < 0)
        currentLine = 0;
    if (currentLine >= vec.size())
        currentLine = vec.size() - 1;

    int startIdx = currentLine;
    int endIdx =
        std::min(currentLine + maxLines, static_cast<int>(vec.size()) - 1);

    for (int i = startIdx; i <= endIdx; i++) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                (*vec[i]).getTitle().c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                (*vec[i]).getTitle().c_str());
        }
    }
}

template <typename T>
void UserInterface::printMapInsideBox(
    MusicLibrary &ml, WINDOW *mainWin, int &currentLine,
    const std::unordered_map<std::string, T> &map) {

    int maxLines = mainWin->_maxy - 2;
    int index = 0;

    for (auto it = map.begin(); it != map.end(); it++) {
        if (index >= currentLine && index < currentLine + maxLines) {
            if (index == currentLine) {
                attron(A_REVERSE);
                mvprintw(
                    mainWin->_begy + index - currentLine + 1,
                    mainWin->_begx + 1, "%s",
                    it->second.getAlbumName().c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(
                    mainWin->_begy + index - currentLine + 1,
                    mainWin->_begx + 1, "%s",
                    it->second.getAlbumName().c_str());
            }
        }
        index++;
    }
}

template <typename T>
void UserInterface::moveDownVector(std::vector<T> &vec, int &currentLine) {
    if (currentLine < vec.size() - 1) {
        currentLine++;
    }
}

void moveDownVector(
    const std::vector<std::shared_ptr<Song>> &vec, int &currentLine) {
    if (currentLine < vec.size() - 1) {
        currentLine++;
    }
}

void UserInterface::moveUp(int &currentLine) {
    if (currentLine > 0) {
        currentLine--;
    }
}

void UserInterface::moveDown(int &currentLine) {
    if (currentLine < defaultMenu.size() - 1) {
        currentLine++;
    }
}

void UserInterface::printMenu(int &currentLine) {
    for (int i = 0; i < 4; i++) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(1 + i, 1, "%s", defaultMenu[i].c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(1 + i, 1, "%s", defaultMenu[i].c_str());
        }
    }
}

void UserInterface::printStatus(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.isDequeEmpty()) {
        mvprintw(
            topWin->_begy + 1, topWin->_begx + 10, "%s",
            musicStatus[2].c_str());
    } else if (ap.checkMusicPlaying()) {
        mvprintw(1, 1, "%s", musicStatus[0].c_str());
    } else {
        mvprintw(1, 1, "%s", musicStatus[1].c_str());
    }
}

void UserInterface::printProgressBar(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.checkMusicPlaying()) {
        float progressBar = ap.calculateSongProgressBar(ap.getCurrentMusic());
        mvprintw(topWin->_begy + 1, topWin->_begx + 1, "%f", progressBar);
        wrefresh(topWin);
    }
}

void UserInterface::printCurrentSong(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.checkMusicPlaying()) {
        mvprintw(
            topWin->_begy + 1, topWin->_begx + 10, "%s",
            ap.getSongQueueFront()->getTitle().c_str());
    }
}

void UserInterface::initNcurses() {
    initscr();
    refresh();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
}

void UserInterface::processKeyUp(WIN_BOX &winBox) {
    if (winBox.currentBox == 1) {
        moveUp(winBox.currentLine3rdBox);
    } else if (winBox.currentBox == 2) {
        moveUp(winBox.currentLine1stBox);
    }
}

void UserInterface::processKeyDown(WIN_BOX &winBox, MusicLibrary &ml) {
    if (winBox.currentBox == 1) {
        moveDownVector(ml.getSongs(), winBox.currentLine3rdBox);
    } else if (winBox.currentBox == 2) {
        moveDown(winBox.currentLine1stBox);
    }
}

void UserInterface::leftMenuAction(
    WIN_BOX &winBox, MusicLibrary &ml, AudioPlayer &ap) {
    if (winBox.currentLine1stBox == MENU::SONGS) {
        ap.loadSound2Queue(winBox.currentLine3rdBox, ml.getSongs());
    } else if (winBox.currentLine1stBox == MENU::ALBUMS) {
        ap.loadSound2Queue(winBox.currentLine3rdBox, ml.getAlbums());
    } else if (winBox.currentLine1stBox == MENU::SHUFFLE) {
        ap.shuffleQueue();
    }
}

void UserInterface::whichVectorShow(
    WIN_BOX &winBox, MENU_BOOL &menuBool, MusicLibrary &ml, WINDOW *mainWin) {
    if (winBox.currentLine1stBox == MENU::SONGS) {
        menuBool.isSongMenu = true;
        menuBool.isAlbumMenu = false;
        menuBool.isPlaylistMenu = false;

    } else if (winBox.currentLine1stBox == MENU::ALBUMS) {
        menuBool.isSongMenu = false;
        menuBool.isAlbumMenu = true;
        menuBool.isPlaylistMenu = false;
    }
    if (menuBool.isSongMenu && !menuBool.isAlbumMenu &&
        !menuBool.isPlaylistMenu) {
        printVectorInsideBox(
            ml, mainWin, winBox.currentLine3rdBox, ml.getSongs());
    } else if (
        menuBool.isAlbumMenu && !menuBool.isSongMenu &&
        !menuBool.isPlaylistMenu) {
        printVectorInsideBox(
            ml, mainWin, winBox.currentLine3rdBox, ml.getAlbums());
    }

    printMenu(winBox.currentLine1stBox);
}