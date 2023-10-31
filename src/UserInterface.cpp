#include "../include/Audio-player/UserInterface.hpp"
#include <unistd.h>

void UserInterface::createWindow(MusicLibrary &ml, AudioPlayer &ap) {
    WIN win, win2, win3;
    int ch;

    initscr();
    refresh();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    WIN_BOX winBox = {0, 0, 1};
    std::thread playbackThread;

    do {
        initWinParams(&win);
        win.height = LINES - 1;
        win.width = COLS / 3 - 15;
        printWinParams(&win);

        initWinParams(&win2);
        win2.height = LINES / 5 - 1;
        win2.width = COLS - 12;
        win2.startx = COLS / 3 - 14;
        printWinParams(&win2);

        initWinParams(&win3);
        win3.starty = LINES / 5 - 1;
        win3.height = LINES - win3.starty - 1;
        win3.width = COLS - 12;
        win3.startx = COLS / 3 - 14;
        printWinParams(&win3);
        clear();
        createBoxes(&win, &win2, &win3);
        moveKeysScreen(ml, ap, &win, &win2, &win3, ch, winBox, playbackThread);
        refresh();

    } while ((ch = getch()) != KEY_F(1));

    if (playbackThread.joinable())
        playbackThread.join();

    endwin();
}

void UserInterface::printWinParams(WIN *p_win) {
#ifdef _DEBUG
    mvprintw(
        25, 0, "%d %d %d %d", p_win->startx, p_win->starty, p_win->width,
        p_win->height);
    refresh();
#endif
}

void UserInterface::initWinParams(WIN *p_win) {
    p_win->height = LINES;
    p_win->width = COLS / 3;
    p_win->starty = 0;
    p_win->startx = 0;

    p_win->border.ls = '|';
    p_win->border.rs = '|';
    p_win->border.ts = '-';
    p_win->border.bs = '-';
    p_win->border.tl = '+';
    p_win->border.tr = '+';
    p_win->border.bl = '+';
    p_win->border.br = '+';
}

void UserInterface::createBoxes(WIN *box1, WIN *box2, WIN *box3) {
    drawBorders(*box1);
    drawBorders(*box2);
    drawBorders(*box3);
}

void UserInterface::changeDir(fs::path *nDirectory) {
    std::cout << "Where to look for songs? Please provide the full path: ";
    std::cin >> *nDirectory;
}

void UserInterface::drawBorders(WIN &box) {
    int i, j;

    for (j = box.starty; j < box.starty + box.height; ++j) {
        for (i = box.startx; i < box.startx + box.width; ++i) {
            mvaddch(j, i, ' ');
        }
    }

    mvaddch(box.starty, box.startx, box.border.tl);
    mvaddch(box.starty, box.startx + box.width, box.border.tr);
    mvaddch(box.starty + box.height, box.startx, box.border.bl);
    mvaddch(box.starty + box.height, box.startx + box.width, box.border.br);
    mvhline(box.starty, box.startx + 1, box.border.ts, box.width - 1);
    mvhline(
        box.starty + box.height, box.startx + 1, box.border.bs, box.width - 1);
    mvvline(box.starty + 1, box.startx, box.border.ls, box.height - 1);
    mvvline(
        box.starty + 1, box.startx + box.width, box.border.rs, box.height - 1);
}

void UserInterface::printSongsInsideBox(
    MusicLibrary &ml, int startY, int startX, int height, int width,
    int &currentLine) {
    std::vector<Song> vec = ml.getSongs();

    int maxLines = height - 2;

    if (currentLine < 0)
        currentLine = 0;
    if (currentLine >= vec.size())
        currentLine = vec.size() - 1;

    int startIdx = currentLine;
    int endIdx =
        std::min(currentLine + maxLines, static_cast<int>(vec.size()) - 1);

    for (int i = startIdx; i <= endIdx; ++i) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(
                startY + i - currentLine + 1, startX + 1, "%s",
                vec[i].getTitle().c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                startY + i - currentLine + 1, startX + 1, "%s",
                vec[i].getTitle().c_str());
        }
    }
}

void UserInterface::moveKeysScreen(
    MusicLibrary &ml, AudioPlayer &ap, WIN *win1, WIN *win2, WIN *win3, int &ch,
    WIN_BOX &winBox, std::thread &playbackThread) {
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
            moveDownVector(ml.getSongs(), winBox.currentLine3rdBox);
        } else if (winBox.currentBox == 2) {
            moveDown(winBox.currentLine1stBox);
        }
        break;
    case KEY_F(4):
        if (winBox.currentBox == 1) {
            ap.loadSound2Queue(winBox.currentLine3rdBox, ml.getSongs());
        } else if (winBox.currentBox == 2 && winBox.currentLine1stBox == 0) {
            if (!playbackThread.joinable())
                playbackThread = std::thread([&ap]() { ap.playQueue(); });
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

    case char('p'):
        ap.pauseOrResumeMusic(ap.getCurrentMusic());
    }

    printSongsInsideBox(
        ml, win3->starty, win3->startx, win3->height, win3->width,
        winBox.currentLine3rdBox);
    printMenu(winBox.currentLine1stBox);
}

template <typename T>
void UserInterface::moveDownVector(std::vector<T> &vec, int &currentLine) {
    if (currentLine < vec.size() - 1) {
        ++currentLine;
    }
}

void UserInterface::moveUp(int &currentLine) {
    if (currentLine > 0) {
        --currentLine;
    }
}

void UserInterface::moveDown(int &currentLine) {
    if (currentLine < defaultMenu.size() - 1) {
        ++currentLine;
    }
}

void UserInterface::printMenu(int &currentLine) {
    for (int i = 0; i < 7; ++i) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(1 + i, 1, "%s", defaultMenu[i].c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(1 + i, 1, "%s", defaultMenu[i].c_str());
        }
    }
}

void UserInterface::printStatus(AudioPlayer &ap) {
    if (ap.isDequeEmpty()) {
        mvprintw(1, 1, "%s", musicStatus[2].c_str());
    } else if (ap.checkMusicPlaying()) {
        mvprintw(1, 1, "%s", musicStatus[0].c_str());
    } else {
        mvprintw(1, 1, "%s", musicStatus[1].c_str());
    }
}