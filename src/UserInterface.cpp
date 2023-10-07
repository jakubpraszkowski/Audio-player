#include "../include/Audio-player/UserInterface.hpp"

void UserInterface::createWindow()
{
    WIN win, win2, win3;
    int ch;

    initscr();            /* Start curses mode 		*/
    start_color();        /* Start the color functionality */
    cbreak();             /* Line buffering disabled, Pass on
                           * everty thing to me 		*/
    keypad(stdscr, TRUE); /* I need that nifty F1 	*/
    noecho();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    /* Initialize the window parameters */
    init_win_params(&win);
    win.height = LINES - 1;
    win.width = COLS / 3 - 15;
    print_win_params(&win);
    init_win_params(&win2);
    win2.height = LINES / 5 - 1;
    win2.width = COLS - 3;
    win2.startx = COLS / 3 - 14;
    // print_win_params(&win2);
    // init_win_params(&win3);
    // win3.height = LINES - 2;
    // win3.width = COLS / 3 - 2;
    // win3.startx = 2 * COLS / 3;
    // print_win_params(&win3);

    attron(COLOR_PAIR(1));
    printw("Press F1 to exit");
    refresh();
    attroff(COLOR_PAIR(1));

    create_boxes(&win, &win2, &win3);
    while ((ch = getch()) != KEY_F(1))
        ;
    endwin(); /* End curses mode		  */
}

void UserInterface::print_win_params(WIN *p_win)
{
#ifdef _DEBUG
    mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
             p_win->width, p_win->height);
    refresh();
#endif
}

void UserInterface::init_win_params(WIN *p_win)
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

void UserInterface::create_boxes(WIN *box1, WIN *box2, WIN *box3)
{
    int i, j;

    // Create box 1
    for (j = box1->starty; j < box1->starty + box1->height; ++j)
    {
        for (i = box1->startx; i < box1->startx + box1->width; ++i)
        {
            mvaddch(j, i, ' ');
        }
    }
    // Draw borders
    mvaddch(box1->starty, box1->startx, box1->border.tl);
    mvaddch(box1->starty, box1->startx + box1->width, box1->border.tr);
    mvaddch(box1->starty + box1->height, box1->startx, box1->border.bl);
    mvaddch(box1->starty + box1->height, box1->startx + box1->width, box1->border.br);
    mvhline(box1->starty, box1->startx + 1, box1->border.ts, box1->width - 1);
    mvhline(box1->starty + box1->height, box1->startx + 1, box1->border.bs, box1->width - 1);
    mvvline(box1->starty + 1, box1->startx, box1->border.ls, box1->height - 1);
    mvvline(box1->starty + 1, box1->startx + box1->width, box1->border.rs, box1->height - 1);

    // Create box 2
    for (j = box2->starty; j < box2->starty + box2->height; ++j)
    {
        for (i = box2->startx; i < box2->startx + box2->width; ++i)
        {
            mvaddch(j, i, ' ');
        }
    }
    // Draw borders
    mvaddch(box2->starty, box2->startx, box2->border.tl);
    mvaddch(box2->starty, box2->startx + box2->width, box2->border.tr);
    mvaddch(box2->starty + box2->height, box2->startx, box2->border.bl);
    mvaddch(box2->starty + box2->height, box2->startx + box2->width, box2->border.br);
    mvhline(box2->starty, box2->startx + 1, box2->border.ts, box2->width - 1);
    mvhline(box2->starty + box2->height, box2->startx + 1, box2->border.bs, box2->width - 1);
    mvvline(box2->starty + 1, box2->startx, box2->border.ls, box2->height - 1);
    mvvline(box2->starty + 1, box2->startx + box2->width, box2->border.rs, box2->height - 1);

    // Create box 3
    for (j = box3->starty; j < box3->starty + box3->height; ++j)
    {
        for (i = box3->startx; i < box3->startx + box3->width; ++i)
        {
            mvaddch(j, i, ' ');
        }
    }
    // Draw borders
    mvaddch(box3->starty, box3->startx, box3->border.tl);
    mvaddch(box3->starty, box3->startx + box3->width, box3->border.tr);
    mvaddch(box3->starty + box3->height, box3->startx, box3->border.bl);
    mvaddch(box3->starty + box3->height, box3->startx + box3->width, box3->border.br);
    mvhline(box3->starty, box3->startx + 1, box3->border.ts, box3->width - 1);
    mvhline(box3->starty + box3->height, box3->startx + 1, box3->border.bs, box3->width - 1);
    mvvline(box3->starty + 1, box3->startx, box3->border.ls, box3->height - 1);
    mvvline(box3->starty + 1, box3->startx + box3->width, box3->border.rs, box3->height - 1);
}

void UserInterface::changeDir(fs::path *nDirectory)
{
    std::cout << "Where to look for songs? Please provide the full path: ";
    std::cin >> *nDirectory;
}
