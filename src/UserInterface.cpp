#include "../include/Audio-player/UserInterface.hpp"

void UserInterface::EntryPoint() {
    FileManager file_manager;
    file_manager.ScanDirectory();
    MusicLibrary music_library;
    music_library.UpdateSongs(file_manager);
    UserInterface ui;
    ui.input_handler_ = new InputHandler();
    ui.win_box_ = new WinBox();
    AudioPlayer audio_player;
    ui.DrawWindowsOnScreen(music_library, audio_player);
}

UserInterface::~UserInterface() {
    if (input_handler_) {
        delete input_handler_;
    }

    if (win_box_) {
        delete win_box_;
    }
}

void UserInterface::DrawWindowsOnScreen(
    MusicLibrary &music_library, AudioPlayer &audio_player) {
    int ch;
    InitNcurses();
    std::thread playback_thread;

    do {
        window_manager_.CreateWindows();
        input_handler_->HandleInput(
            music_library, audio_player, ch, playback_thread, *win_box_, *this);
        WhichVectorShow(music_library);
        PrintCurrentSong(audio_player);
        RefreshWindows();
    } while ((ch = getch()) != KEY_F(1));

    if (playback_thread.joinable())
        playback_thread.join();

    endwin();
    delwin(stdscr);
}

int UserInterface::get_menu_size() { return static_cast<int>(Menu::MENU_SIZE); }

void UserInterface::MoveOnScreenWithKeys(
    MusicLibrary &music_library, AudioPlayer &audio_player, int &ch,
    std::thread &playback_thread) {
    InputHandler input_handler;
    input_handler.HandleInput(
        music_library, audio_player, ch, playback_thread, *win_box_, *this);
}

template <typename T>
void UserInterface::PrintVectorInsideWindow(
    MusicLibrary &music_library, WINDOW *main_win, int &current_line,
    std::vector<T> &vec) {
    if (vec.empty()) {
        if (typeid(T) == typeid(Playlist)) {
            NoPlaylists();
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
    wrefresh(main_win);
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
    wrefresh(main_win);
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

void UserInterface::PrintStatus(AudioPlayer &audio_player) {
    if (audio_player.is_deque_empty()) {
        mvprintw(
            getbegy(window_manager_.get_top_window()) + 1,
            getbegx(window_manager_.get_top_window()) + 10, "%s",
            music_status[2].c_str());
    } else if (audio_player.check_music_playing()) {
        mvprintw(1, 1, "%s", music_status[0].c_str());
    } else {
        mvprintw(1, 1, "%s", music_status[1].c_str());
    }
}

void UserInterface::PrintProgressBar(AudioPlayer &audio_player) {
    if (audio_player.check_music_playing()) {
        float progress_bar = audio_player.CalculateSongProgressBar();
        int progress_bar_length = static_cast<int>(progress_bar * 100);

        mvwprintw(
            window_manager_.get_top_window(),
            getbegy(window_manager_.get_top_window()) + 1,
            getbegx(window_manager_.get_top_window()) + 11, "[");
        wattron(window_manager_.get_top_window(), A_REVERSE);
        for (int i = 0; i < progress_bar_length; ++i) {
            wprintw(window_manager_.get_top_window(), "=");
        }
        wattroff(window_manager_.get_top_window(), A_REVERSE);
        for (int i = progress_bar_length; i < 20; ++i) {
            wprintw(window_manager_.get_top_window(), " ");
        }
        wprintw(window_manager_.get_top_window(), "]");

        wrefresh(window_manager_.get_top_window());
    }
}

void UserInterface::PrintCurrentSong(AudioPlayer &audio_player) {
    if (audio_player.check_music_playing()) {
        mvprintw(
            getbegy(window_manager_.get_top_window()) + 1,
            getbegx(window_manager_.get_top_window()) + 10, "%s",
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

void UserInterface::LeftMenuAction(
    MusicLibrary &music_library, AudioPlayer &audio_player) {
    if (win_box_->current_line_1st_box == static_cast<int>(Menu::SONGS)) {
        audio_player.LoadSoundToQueue(
            win_box_->current_line_3rd_box, music_library.get_songs());
    } else if (
        win_box_->current_line_1st_box == static_cast<int>(Menu::ALBUMS)) {
        audio_player.LoadSoundToQueue(
            win_box_->current_line_3rd_box, music_library.get_albums());
    } else if (
        win_box_->current_line_1st_box == static_cast<int>(Menu::SHUFFLE)) {
        audio_player.ShuffleQueue();
    } else if (
        win_box_->current_line_1st_box == static_cast<int>(Menu::PLAYLISTS)) {
    }
}

void UserInterface::WhichVectorShow(MusicLibrary &music_library) {
    UpdateMenuState();

    if (menu_bool_.is_song_menu && !menu_bool_.is_album_menu &&
        !menu_bool_.is_playlist_menu) {
        ShowSongs(music_library);
    } else if (
        menu_bool_.is_album_menu && !menu_bool_.is_song_menu &&
        !menu_bool_.is_playlist_menu) {
        ShowAlbums(music_library);
    } else if (
        !menu_bool_.is_album_menu && !menu_bool_.is_song_menu &&
        menu_bool_.is_playlist_menu) {
        ShowPlaylists(music_library);
    }

    PrintMenu<Menu>(win_box_->current_line_1st_box, [this](Menu menu) {
        return this->get_menu_option(menu);
    });
}

void UserInterface::UpdateUi(AudioPlayer &audio_player) {
    if (audio_player.check_music_playing()) {
        while (true) {
            PrintProgressBar(audio_player);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void UserInterface::StatusThread(AudioPlayer &audio_player) {
    std::thread ui_thread(
        &UserInterface::UpdateUi, this, std::ref(audio_player));
    ui_thread.detach();
}

void UserInterface::CreatePlaylistMenu(MusicLibrary &music_library) {
    wrefresh(window_manager_.get_main_window());
    mvprintw(
        getbegy(window_manager_.get_top_window()) + 1,
        getbegx(window_manager_.get_top_window()) + 10, "%s",
        "Playlist Creation Mode");
    mvprintw(
        getbegy(window_manager_.get_top_window()) + 3,
        getbegx(window_manager_.get_top_window()) + 10, "%s",
        "Enter playlist name: ");
    std::string input;
    int ch;
    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE && !input.empty()) {
            input.pop_back();
            mvprintw(
                getbegy(window_manager_.get_top_window()) + 3,
                getbegx(window_manager_.get_top_window()) + 30, "");
        } else if (isprint(ch)) {
            input.push_back(ch);
        };
        mvprintw(
            getbegy(window_manager_.get_top_window()) + 3,
            getbegx(window_manager_.get_top_window()) + 30, "%s",
            input.c_str());
    }
    Playlist new_playlist(input);
    music_library.AddPlaylist(new_playlist);
    wrefresh(window_manager_.get_top_window());
}

void UserInterface::NoPlaylists() {
    mvprintw(
        getbegy(window_manager_.get_main_window()) + 1,
        getbegx(window_manager_.get_main_window()) + 1, "%s",
        "No playlists created yet");
}

void UserInterface::PlaylistMenuI() {
    wrefresh(window_manager_.get_sidebar_window());
    wrefresh(window_manager_.get_main_window());
}

void UserInterface::ShowSongs(MusicLibrary &music_library) {
    PrintVectorInsideWindow(
        music_library, window_manager_.get_main_window(),
        win_box_->current_line_3rd_box, music_library.get_songs());
}

void UserInterface::ShowAlbums(MusicLibrary &music_library) {
    PrintVectorInsideWindow(
        music_library, window_manager_.get_main_window(),
        win_box_->current_line_3rd_box, music_library.get_albums());
}

void UserInterface::ShowPlaylists(MusicLibrary &music_library) {
    PrintVectorInsideWindow(
        music_library, window_manager_.get_main_window(),
        win_box_->current_line_3rd_box, music_library.get_playlists());
}

void UserInterface::UpdateMenuState() {
    menu_bool_.is_song_menu =
        (win_box_->current_line_1st_box == static_cast<int>(Menu::SONGS));
    menu_bool_.is_album_menu =
        (win_box_->current_line_1st_box == static_cast<int>(Menu::ALBUMS));
    menu_bool_.is_playlist_menu =
        (win_box_->current_line_1st_box == static_cast<int>(Menu::PLAYLISTS));
}

void UserInterface::RefreshWindows() { window_manager_.RefreshWindows(); }

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
