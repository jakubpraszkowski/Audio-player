#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/KeyboardInteraction.hpp"

const std::array<std::string, 4> UserInterface::optionMenu = {
    "Play", "Songs", "Albums", "Playlists"};

void UserInterface::changeDir(fs::path nDirectory) {
    std::cout << "Where to look for songs? Please provide the full path: ";
    std::cin >> nDirectory;
}

const std::array<std::string, 4> &UserInterface::getOptionMenu() {
    return optionMenu;
}

template <typename T>
void UserInterface::printVectorInsideBox(
    MusicLibrary &ml, WINDOW *mainWin, int &currentLine, std::vector<T> &vec) {

    int maxLines = mainWin->_maxy - 2;

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
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                vec[i].getTitle().c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                mainWin->_begy + i - currentLine + 1, mainWin->_begx + 1, "%s",
                vec[i].getTitle().c_str());
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

    for (int i = startIdx; i <= endIdx; ++i) {
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

    for (auto it = map.begin(); it != map.end(); ++it) {
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
        ++index;
    }
}

void UserInterface::printMenu(int &currentLine) {
    for (int i = 0; i < 4; ++i) {
        if (i == currentLine) {
            attron(A_REVERSE);
            mvprintw(1 + i, 1, "%s", optionMenu[i].c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(1 + i, 1, "%s", optionMenu[i].c_str());
        }
    }
}

void UserInterface::printProgressBar(AudioPlayer &ap, WINDOW *topWin) {
    if (ap.checkMusicPlaying()) {
        float progressBar = ap.calculateSongProgressBar(ap.getCurrentMusic());
        mvprintw(topWin->_begy + 1, topWin->_begx + 1, "%f", progressBar);
        wrefresh(topWin);
    }
}

void UserInterface::initWindowParams() {
    initscr();
    refresh();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
}

void UserInterface::createProgressBar(AudioPlayer &ap, WINDOW *win) {
    if (ap.checkMusicPlaying()) {
        float progressBar = ap.calculateSongProgressBar(ap.getCurrentMusic());
        mvprintw(win->_begy + 1, win->_begx + 1, "%f", progressBar);
        wrefresh(win);
    }
}

void UserInterface::printCurrentSong(AudioPlayer &ap, WINDOW *win) {
    if (ap.checkMusicPlaying()) {
        mvprintw(
            win->_begy + 1, win->_begx + 1, "%s",
            ap.getPlayingSong()->getTitle().c_str());
        wrefresh(win);
    }
}