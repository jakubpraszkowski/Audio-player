#include "../include/Audio-player/WindowManager.hpp"

void WindowManager::CreateWindows() {
    getmaxyx(stdscr, main_win_params_.height, main_win_params_.width);

    sidebar_win_params_.height = main_win_params_.height;
    top_win_params_.width = main_win_params_.width - sidebar_win_params_.width;
    main_win_params_.height -= top_win_params_.height;
    main_win_params_.width -= sidebar_win_params_.width;

    InitializeWindow(sidebar_win_params_);
    InitializeWindow(top_win_params_);
    InitializeWindow(main_win_params_);
}

void WindowManager::RefreshWindows() {
    wrefresh(top_win_params_.win);
    wrefresh(main_win_params_.win);
    wrefresh(sidebar_win_params_.win);
}

WINDOW* WindowManager::get_top_window() const {
    return top_win_params_.win;
}

WINDOW* WindowManager::get_sidebar_window() const {
    return sidebar_win_params_.win;
}

WINDOW* WindowManager::get_main_window() const {
    return main_win_params_.win;
}

void WindowManager::InitializeWindow(WindowParams& params) {
    params.win = newwin(params.height, params.width, params.y, params.x);
    box(params.win, 0, 0);
}
