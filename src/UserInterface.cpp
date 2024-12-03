#include "../include/Audio-player/UserInterface.hpp"

void UserInterface::EntryPoint() {
    FileManager file_manager;
    file_manager.ScanDirectory();
    MusicLibrary music_library;
    music_library.UpdateSongs(file_manager);
    UserInterface ui;
    AudioPlayer audio_player;
    ui.DrawWindowsOnScreen(music_library, audio_player);
}

void UserInterface::DrawWindowsOnScreen(
    MusicLibrary &music_library, AudioPlayer &audio_player) {
    int ch;
    InitNcurses();
    std::thread playback_thread;
    WindowInit window_init;
    WinBox win_box;

    do {
        create_windows(window_init);

    } while ((ch = getch()) != KEY_F(1));

    if (playback_thread.joinable())
        playback_thread.join();

    endwin();
    delwin(stdscr);
}

void UserInterface::create_windows(WindowInit &window_init) {
    getmaxyx(stdscr, window_init.main_win_height, window_init.main_win_width);

    WINDOW *sidebar_win = newwin(
        window_init.main_win_height, window_init.sidebar_win_width,
        window_init.sidebar_win_y, window_init.sidebar_win_x);
    WINDOW *top_win = newwin(
        window_init.top_win_height,
        window_init.main_win_width - window_init.sidebar_win_width,
        window_init.top_win_y, window_init.sidebar_win_width);
    WINDOW *main_win = newwin(
        window_init.main_win_height - window_init.top_win_height,
        window_init.main_win_width - window_init.sidebar_win_width,
        window_init.top_win_height, window_init.sidebar_win_width);

    box(sidebar_win, 0, 0);
    box(top_win, 0, 0);
    box(main_win, 0, 0);
}

void UserInterface::refresh_windows(
    WINDOW *sidebar_win, WINDOW *top_win, WINDOW *main_win) {
    wrefresh(sidebar_win);
    wrefresh(top_win);
    wrefresh(main_win);
}

void UserInterface::MoveOnScreenWithKeys(
    MusicLibrary &music_library, AudioPlayer &audio_player, WinBox &win_box,
    int &ch, std::thread &playback_thread, WINDOW *main_win, WINDOW *top_win) {
    switch (ch) {
    case '\t':
        win_box.current_box = (win_box.current_box % 2) + 1;
        break;

    case KEY_UP:
        ProcessKeyUp(win_box);
        break;

    case KEY_DOWN:
        ProcessKeyDown(win_box, music_library);
        break;

    case KEY_F(4):
        handle_key_f4(win_box, music_library, audio_player, playback_thread);
        break;

    case KEY_RIGHT:
        if (audio_player.check_music_playing()) {
            audio_player.AdvanceForwardMusic(audio_player.get_current_music());
        }
        break;

    case KEY_LEFT:
        if (audio_player.check_music_playing()) {
            audio_player.AdvanceBackwardMusic(audio_player.get_current_music());
        }
        break;

    case char('s'):
        if (audio_player.check_music_playing()) {
            audio_player.StopMusic(audio_player.get_current_music());
        }
        break;

    case char('p'):
        audio_player.PauseOrResumeMusic(audio_player.get_current_music());
        break;

    default:
        break;
    }

    MenuBool menu_bool;
    WhichVectorShow(win_box, menu_bool, music_library, main_win, top_win);
}

void UserInterface::handle_key_f4(
    WinBox &win_box, MusicLibrary &music_library, AudioPlayer &audio_player,
    std::thread &playback_thread) {
    if (win_box.current_box == 1) {
        LeftMenuAction(win_box, music_library, audio_player);
    } else if (win_box.current_box == 2 && win_box.current_line_1st_box == 0) {
        if (!playback_thread.joinable()) {
            playback_thread =
                std::thread([&audio_player]() { audio_player.PlayQueue(); });
        }
    }
}

template <typename T>
void UserInterface::PrintVectorInsideWindow(
    MusicLibrary &music_library, WINDOW *main_win, int &current_line,
    std::vector<T> &vec) {
    if (vec.empty()) {
        if (typeid(T) == typeid(Playlist)) {
            no_playlists(main_win);
        }
        return;
    }

    int max_lines = getmaxy(main_win) - 2;

    if (current_line < 0)
        current_line = 0;
    if (current_line >= vec.size())
        current_line = vec.size() - 1;

    int start_idx = current_line;
    int end_idx =
        std::min(current_line + max_lines, static_cast<int>(vec.size()) - 1);

    for (int i = start_idx; i <= end_idx; i++) {
        if (i == current_line) {
            wattron(main_win, A_REVERSE);
            mvwprintw(
                main_win, getbegy(main_win) + i - current_line + 1,
                getbegx(main_win) + 1, "%s", vec[i].get_title().c_str());
            wattroff(main_win, A_REVERSE);
        } else {
            mvwprintw(
                main_win, getbegy(main_win) + i - current_line + 1,
                getbegx(main_win) + 1, "%s", vec[i].get_title().c_str());
        }
    }
}

void UserInterface::PrintVectorInsideWindow(
    MusicLibrary &music_library, WINDOW *main_win, int &current_line,
    SongsVector &vec) {
    int max_lines = getmaxy(main_win) - 2;

    if (current_line < 0)
        current_line = 0;
    if (current_line >= vec.size())
        current_line = vec.size() - 1;

    int start_idx = current_line;
    int end_idx =
        std::min(current_line + max_lines, static_cast<int>(vec.size()) - 1);

    for (int i = start_idx; i <= end_idx; i++) {
        if (i == current_line) {
            wattron(main_win, A_REVERSE);
            mvwprintw(
                main_win, getbegy(main_win) + i - current_line + 1,
                getbegx(main_win) + 1, "%s", (*vec[i]).get_title().c_str());
            wattroff(main_win, A_REVERSE);
        } else {
            mvwprintw(
                main_win, getbegy(main_win) + i - current_line + 1,
                getbegx(main_win) + 1, "%s", (*vec[i]).get_title().c_str());
        }
    }
}

template <typename T>
void UserInterface::MoveDown(std::vector<T> &vec, int &current_line) {
    if (current_line < vec.size() - 1) {
        current_line++;
    }
}

void UserInterface::MoveUp(int &current_line) {
    if (current_line > 0) {
        current_line--;
    }
}

void UserInterface::MoveDown(
    int &current_line, std::function<int()> get_size_func) {
    if (current_line < get_size_func() - 1) {
        current_line++;
    }
}

template <typename T>
void UserInterface::PrintMenu(
    int &current_line, std::function<std::string(T)> get_menu_option_func) {
    for (int i = 0; i < static_cast<int>(T::MENU_SIZE); i++) {
        if (i == current_line) {
            attron(A_REVERSE);
            mvprintw(
                1 + i, 1, "%s",
                get_menu_option_func(static_cast<T>(i)).c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(
                1 + i, 1, "%s",
                get_menu_option_func(static_cast<T>(i)).c_str());
        }
    }
}

void UserInterface::PrintStatus(AudioPlayer &audio_player, WINDOW *top_win) {
    if (audio_player.is_deque_empty()) {
        mvprintw(
            getbegy(top_win) + 1, getbegx(top_win) + 10, "%s",
            music_status[2].c_str());
    } else if (audio_player.check_music_playing()) {
        mvprintw(1, 1, "%s", music_status[0].c_str());
    } else {
        mvprintw(1, 1, "%s", music_status[1].c_str());
    }
}

void UserInterface::PrintProgressBar(
    AudioPlayer &audio_player, WINDOW *top_win) {
    if (audio_player.check_music_playing()) {
        float progress_bar = audio_player.CalculateSongProgressBar(
            audio_player.get_current_music());
        int progress_bar_length = static_cast<int>(progress_bar * 100);

        mvwprintw(top_win, getbegy(top_win) + 1, getbegx(top_win) + 11, "[");
        wattron(top_win, A_REVERSE);
        for (int i = 0; i < progress_bar_length; ++i) {
            wprintw(top_win, "=");
        }
        wattroff(top_win, A_REVERSE);
        for (int i = progress_bar_length; i < 20; ++i) {
            wprintw(top_win, " ");
        }
        wprintw(top_win, "]");

        wrefresh(top_win);
    }
}

void UserInterface::PrintCurrentSong(
    AudioPlayer &audio_player, WINDOW *top_win) {
    if (audio_player.check_music_playing()) {
        mvprintw(
            getbegy(top_win) + 1, getbegx(top_win) + 10, "%s",
            audio_player.get_song_queue_front()->get_title().c_str());
    }
}

void UserInterface::InitNcurses() {
    initscr();
    refresh();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}

void UserInterface::ProcessKeyUp(WinBox &win_box) {
    if (win_box.current_box == 1) {
        MoveUp(win_box.current_line_3rd_box);
    } else if (win_box.current_box == 2) {
        MoveUp(win_box.current_line_1st_box);
    }
}

void UserInterface::ProcessKeyDown(
    WinBox &win_box, MusicLibrary &music_library) {
    if (win_box.current_box == 1) {
        MoveDown(music_library.get_songs(), win_box.current_line_3rd_box);
    } else if (win_box.current_box == 2) {
        MoveDown(win_box.current_line_1st_box, []() {
            return static_cast<int>(Menu::MENU_SIZE);
        });
    }
}

void UserInterface::LeftMenuAction(
    WinBox &win_box, MusicLibrary &music_library, AudioPlayer &audio_player) {
    if (win_box.current_line_1st_box == static_cast<int>(Menu::SONGS)) {
        audio_player.LoadSoundToQueue(
            win_box.current_line_3rd_box, music_library.get_songs());
    } else if (win_box.current_line_1st_box == static_cast<int>(Menu::ALBUMS)) {
        audio_player.LoadSoundToQueue(
            win_box.current_line_3rd_box, music_library.get_albums());
    } else if (
        win_box.current_line_1st_box == static_cast<int>(Menu::SHUFFLE)) {
        audio_player.ShuffleQueue();
    } else if (
        win_box.current_line_1st_box == static_cast<int>(Menu::PLAYLISTS)) {
    }
}

void UserInterface::WhichVectorShow(
    WinBox &win_box, MenuBool &menu_bool, MusicLibrary &music_library,
    WINDOW *main_win, WINDOW *top_win) {
    if (win_box.current_line_1st_box == static_cast<int>(Menu::SONGS)) {
        menu_bool.is_song_menu = true;
        menu_bool.is_album_menu = false;
        menu_bool.is_playlist_menu = false;

    } else if (win_box.current_line_1st_box == static_cast<int>(Menu::ALBUMS)) {
        menu_bool.is_song_menu = false;
        menu_bool.is_album_menu = true;
        menu_bool.is_playlist_menu = false;

    } else if (
        win_box.current_line_1st_box == static_cast<int>(Menu::PLAYLISTS)) {
        menu_bool.is_song_menu = false;
        menu_bool.is_album_menu = false;
        menu_bool.is_playlist_menu = true;
    }

    if (menu_bool.is_song_menu && !menu_bool.is_album_menu &&
        !menu_bool.is_playlist_menu) {

        PrintVectorInsideWindow(
            music_library, main_win, win_box.current_line_3rd_box,
            music_library.get_songs());
    } else if (
        menu_bool.is_album_menu && !menu_bool.is_song_menu &&
        !menu_bool.is_playlist_menu) {
        PrintVectorInsideWindow(
            music_library, main_win, win_box.current_line_3rd_box,
            music_library.get_albums());
    } else if (
        !menu_bool.is_album_menu && !menu_bool.is_song_menu &&
        menu_bool.is_playlist_menu) {
        PrintVectorInsideWindow(
            music_library, main_win, win_box.current_line_3rd_box,
            music_library.get_playlists());
    }

    PrintMenu<Menu>(win_box.current_line_1st_box, [this](Menu menu) {
        return this->get_menu_option(menu);
    });
}

void UserInterface::UpdateUI(AudioPlayer &audio_player, WINDOW *top_win) {
    if (audio_player.check_music_playing()) {
        while (true) {
            PrintProgressBar(audio_player, top_win);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void UserInterface::StatusThread(AudioPlayer &audio_player, WINDOW *top_win) {
    std::thread ui_thread(
        &UserInterface::UpdateUI, this, std::ref(audio_player), top_win);
    ui_thread.detach();
}

void UserInterface::CreatePlaylistMenu(
    WINDOW *top_win, int &ch, MusicLibrary &music_library, WINDOW *main_win) {
    wrefresh(main_win);
    mvprintw(
        getbegy(top_win) + 1, getbegx(top_win) + 10, "%s",
        "Playlist Creation Mode");
    mvprintw(
        getbegy(top_win) + 3, getbegx(top_win) + 10, "%s",
        "Enter playlist name: ");
    std::string input;
    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE && !input.empty()) {
            input.pop_back();
            mvprintw(getbegy(top_win) + 3, getbegx(top_win) + 30, "");
        } else if (isprint(ch)) {
            input.push_back(ch);
        };
        mvprintw(
            getbegy(top_win) + 3, getbegx(top_win) + 30, "%s", input.c_str());
    }
    Playlist new_playlist(input);
    music_library.AddPlaylist(new_playlist);
    wrefresh(top_win);
}

std::string UserInterface::get_menu_option(Menu menu) {
    switch (menu) {
    case Menu::PLAY:
        return "Play";
    case Menu::SONGS:
        return "Songs";
    case Menu::ALBUMS:
        return "Albums";
    case Menu::SHUFFLE:
        return "Shuffle";
    case Menu::PLAYLISTS:
        return "Playlists";
    default:
        return "UNKNOWN";
    }
}

std::string
UserInterface::get_playlist_menu_option(PlaylistMenu playlist_menu) {
    switch (playlist_menu) {
    case PlaylistMenu::ADD_SONG:
        return "Add song";
    case PlaylistMenu::CREATE:
        return "Create";
    case PlaylistMenu::DELETE:
        return "Delete";
    case PlaylistMenu::SHOW:
        return "Show";
    case PlaylistMenu::REMOVE_SONG:
        return "Remove song";
    case PlaylistMenu::GO_BACK:
        return "Go back";
    default:
        return "UNKNOWN";
    }
}

void UserInterface::NoPlaylists(WINDOW *main_win) {
    mvprintw(
        getbegy(main_win) + 1, getbegx(main_win) + 1, "%s",
        "No playlists created yet");
}

void UserInterface::PlaylistMenuI(
    WINDOW *side_bar_win, int &ch, MusicLibrary &music_library,
    WINDOW *main_win) {
    wrefresh(side_bar_win);
    wrefresh(main_win);
}
