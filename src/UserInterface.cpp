#include "../include/Audio-player/UserInterface.hpp"

void UserInterface::createWindow(MusicLibrary &ml)
{
    WIN win, win2, win3;
    int ch;

    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    initWinParams(&win);
    win.height = LINES - 1;
    win.width = COLS / 3 - 15;
    printWinParams(&win);
    initWinParams(&win2);
    win2.height = LINES / 5 - 1;
    win2.width = COLS - 3;
    win2.startx = COLS / 3 - 14;
    printWinParams(&win2);
    initWinParams(&win3);
    win3.starty = LINES / 5 - 1;
    win3.height = LINES - win3.starty;
    win3.width = COLS - 10;
    win3.startx = COLS / 3 - 14;
    printWinParams(&win3);

    attron(COLOR_PAIR(1));
    printw("Press F1 to exit");
    refresh();
    attroff(COLOR_PAIR(1));

    createBoxes(&win, &win2, &win3);

    attron(COLOR_PAIR(1));

    printSongsInsideBox(ml, win3.starty, win3.startx, win3.height, win3.width);
    attroff(COLOR_PAIR(1));
    while ((ch = getch()) != KEY_F(1))
        ;
    endwin();
}

void UserInterface::printWinParams(WIN *p_win)
{
#ifdef _DEBUG
    mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
             p_win->width, p_win->height);
    refresh();
#endif
}

void UserInterface::initWinParams(WIN *p_win)
{
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

void UserInterface::createBoxes(WIN *box1, WIN *box2, WIN *box3)
{
    drawBorders(*box1);
    drawBorders(*box2);
    drawBorders(*box3);
}

void UserInterface::changeDir(fs::path *nDirectory)
{
    std::cout << "Where to look for songs? Please provide the full path: ";
    std::cin >> *nDirectory;
}

void UserInterface::drawBorders(WIN &box)
{
    int i, j;

    for (j = box.starty; j < box.starty + box.height; ++j)
    {
        for (i = box.startx; i < box.startx + box.width; ++i)
        {
            mvaddch(j, i, ' ');
        }
    }

    mvaddch(box.starty, box.startx, box.border.tl);
    mvaddch(box.starty, box.startx + box.width, box.border.tr);
    mvaddch(box.starty + box.height, box.startx, box.border.bl);
    mvaddch(box.starty + box.height, box.startx + box.width, box.border.br);
    mvhline(box.starty, box.startx + 1, box.border.ts, box.width - 1);
    mvhline(box.starty + box.height, box.startx + 1, box.border.bs, box.width - 1);
    mvvline(box.starty + 1, box.startx, box.border.ls, box.height - 1);
    mvvline(box.starty + 1, box.startx + box.width, box.border.rs, box.height - 1);
}

void UserInterface::printSongsInsideBox(MusicLibrary &ml, int startY, int startX, int height, int width)
{
    std::vector<Song> vec = ml.getSongs();
    int maxLines = std::min(int(vec.size()), height - 2);
    for (int i = 0; i < maxLines; ++i)
    {
        mvprintw(startY + i + 1, startX + 1, "%s", vec[i].getTitle().c_str());
    }
}