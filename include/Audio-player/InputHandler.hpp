#pragma once

#include <functional>
#include <thread>

#include <ncurses/ncurses.h>

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include "UserInterface.hpp"

class UserInterface;

struct WinBox {
    int current_line_1st_box = 0;
    int current_line_3rd_box = 0;
    int current_box = 2;
};

class InputHandler {
  public:
    InputHandler();

    void HandleF4Key(
        MusicLibrary &music_library, AudioPlayer &audio_player,
        std::thread &playback_thread, WinBox &win_box, UserInterface &ui);
    void HandleInput(
        MusicLibrary &music_library, AudioPlayer &audio_player, int &ch,
        std::thread &playback_thread, WinBox &win_box, UserInterface &ui);

    ~InputHandler();

  private:
    void ProcessKeyUp(WinBox &win_box);
    void ProcessKeyDown(MusicLibrary &music_library, WinBox &win_box);
    void MoveUp(int &current_line);
    void MoveDown(int &current_line, std::function<int()> get_size_func);

    UserInterface *ui;
};
