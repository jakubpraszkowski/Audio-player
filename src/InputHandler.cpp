#include "../include/Audio-player/InputHandler.hpp"

InputHandler::InputHandler() { ui = new UserInterface(); }

InputHandler::~InputHandler() {
    if (ui) {
        delete ui;
    }
}

void InputHandler::HandleInput(
    MusicLibrary &music_library, AudioPlayer &audio_player, int &ch,
    std::thread &playback_thread, WinBox &win_box, UserInterface &ui) {
    printw("Handling input: %d\n", ch);
    refresh();
    switch (ch) {
    case '\t':
        win_box.current_box = (win_box.current_box % 2) + 1;
        break;

    case KEY_UP:
        ProcessKeyUp(win_box);
        break;

    case KEY_DOWN:
        ProcessKeyDown(music_library, win_box);
        break;

    case KEY_F(4):
        HandleF4Key(music_library, audio_player, playback_thread, win_box, ui);
        break;

    case KEY_RIGHT:
        if (audio_player.check_music_playing()) {
            audio_player.AdvanceForwardMusic();
        }
        break;

    case KEY_LEFT:
        if (audio_player.check_music_playing()) {
            audio_player.AdvanceBackwardMusic();
        }
        break;

    case 's':
        if (audio_player.check_music_playing()) {
            audio_player.StopMusic();
        }
        break;

    case 'p':
        audio_player.PauseOrResumeMusic();
        break;

    default:
        break;
    }

    ui.WhichVectorShow(music_library);
    ui.PrintCurrentSong(audio_player);
    ui.RefreshWindows();
}

void InputHandler::ProcessKeyUp(WinBox &win_box) {
    if (win_box.current_box == 1) {
        MoveUp(win_box.current_line_3rd_box);
    } else if (win_box.current_box == 2) {
        MoveUp(win_box.current_line_1st_box);
    }
}

void InputHandler::ProcessKeyDown(
    MusicLibrary &music_library, WinBox &win_box) {
    if (win_box.current_box == 1) {
        MoveDown(win_box.current_line_3rd_box, [&]() {
            return music_library.get_songs().size();
        });
    } else if (win_box.current_box == 2) {
        MoveDown(win_box.current_line_1st_box, []() {
            return UserInterface::get_menu_size();
        });
    }
}

void InputHandler::MoveUp(int &current_line) {
    if (current_line > 0) {
        --current_line;
    }
}

void InputHandler::MoveDown(
    int &current_line, std::function<int()> get_size_func) {
    if (current_line < get_size_func() - 1) {
        ++current_line;
    } else {
        current_line = 0;
    }
}

void InputHandler::HandleF4Key(
    MusicLibrary &music_library, AudioPlayer &audio_player,
    std::thread &playback_thread, WinBox &win_box, UserInterface &ui) {
    if (win_box.current_box == 1) {
        ui.LeftMenuAction(music_library, audio_player);
    } else if (win_box.current_box == 2 && win_box.current_line_1st_box == 0) {
        if (!playback_thread.joinable()) {
            playback_thread =
                std::thread([&audio_player]() { audio_player.PlayQueue(); });
        }
    }
}
