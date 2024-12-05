#pragma once

#include <ncurses/ncurses.h>

class WindowManager {
  public:
    void CreateWindows();
    void RefreshWindows();

    WINDOW *get_top_window() const;
    WINDOW *get_sidebar_window() const;
    WINDOW *get_main_window() const;

  private:
    struct WindowParams {
        int width;
        int height;
        int x;
        int y;
        WINDOW *win;
    };

    WindowParams sidebar_win_params_ = {30, 0, 0, 0, nullptr};
    WindowParams top_win_params_ = {0, 3, 0, 0, nullptr};
    WindowParams main_win_params_ = {0, 0, 0, 0, nullptr};

    void InitializeWindow(WindowParams &params);
};
