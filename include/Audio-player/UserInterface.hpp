#pragma once

#include <unistd.h>

#include <array>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

#include <ncurses/ncurses.h>

#include "AudioPlayer.hpp"
#include "MusicLibrary.hpp"
#include "Playlist.hpp"
#include "Song.hpp"

class UserInterface {
  private:
    struct WinBox;
    struct MenuBool;
    struct WindowInit;
    enum class Menu;
    enum class PlaylistMenu;

  public:
    using SongsVector = std::vector<std::shared_ptr<Song>>;

    static void EntryPoint();

    void DrawWindowsOnScreen(MusicLibrary &ml, AudioPlayer &ap);

    void create_windows(WindowInit &window_init);

    void
    refresh_windows(WINDOW *sidebar_win, WINDOW *top_win, WINDOW *main_win);

    void MoveOnScreenWithKeys(
        MusicLibrary &ml, AudioPlayer &ap, WinBox &win_box, int &ch,
        std::thread &playback_thread, WINDOW *win, WINDOW *top_win);

    void handle_key_f4(
        WinBox &win_box, MusicLibrary &music_library, AudioPlayer &audio_player,
        std::thread &playback_thread);

    void PrintVectorInsideWindow(
        MusicLibrary &ml, WINDOW *main_win, int &current_line,
        SongsVector &vec);

    template <typename T>
    void PrintVectorInsideWindow(
        MusicLibrary &ml, WINDOW *win, int &current_line, std::vector<T> &vec);

    template <typename T> void MoveDown(std::vector<T> &vec, int &current_line);

    void MoveDown(int &current_line, std::function<int()> get_size_func);

    void MoveUp(int &current_line);

    template <typename T>
    void PrintMenu(
        int &current_line, std::function<std::string(T)> get_menu_option_func);

    void PrintStatus(AudioPlayer &ap, WINDOW *top_win);

    void PrintProgressBar(AudioPlayer &ap, WINDOW *top_win);

    void PrintCurrentSong(AudioPlayer &ap, WINDOW *top_win);

    void InitNcurses();

    void ProcessKeyUp(WinBox &win_box);

    void ProcessKeyDown(WinBox &win_box, MusicLibrary &ml);

    void LeftMenuAction(WinBox &win_box, MusicLibrary &ml, AudioPlayer &ap);

    void WhichVectorShow(
        WinBox &win_box, MenuBool &menu_bool, MusicLibrary &ml,
        WINDOW *main_win, WINDOW *top_win);

    void UpdateUI(AudioPlayer &ap, WINDOW *top_win);

    void StatusThread(AudioPlayer &ap, WINDOW *top_win);

    void CreatePlaylistMenu(
        WINDOW *top_win, int &ch, MusicLibrary &ml, WINDOW *main_win);

    std::string get_menu_option(Menu menu);

    std::string get_playlist_menu_option(PlaylistMenu playlist_menu);

    void NoPlaylists(WINDOW *main_win);

    void PlaylistMenuI(
        WINDOW *sidebar_win, int &ch, MusicLibrary &ml, WINDOW *main_win);

  private:
    struct WinBox {
        int current_line_1st_box = 0;
        int current_line_3rd_box = 0;
        int current_box = 2;
    };

    struct WindowInit {
        int main_win_width = 0;
        int main_win_height = 0;
        int sidebar_win_width = 20;
        int sidebar_win_x = 0;
        int sidebar_win_y = 0;
        int top_win_height = 5;
        int top_win_y = 0;
        int main_win_y = 0;
        int main_win_x = 0;
    };

    struct MenuBool {
        bool is_song_menu = false;
        bool is_album_menu = false;
        bool is_playlist_menu = false;
    };

    struct PlaylistMenuBool {
        bool is_show_menu = false;
        bool is_create_menu = false;
        bool is_delete_menu = false;
        bool is_add_song_menu = false;
        bool is_remove_song_menu = false;
    };

    enum class Menu { PLAY, SONGS, ALBUMS, PLAYLISTS, SHUFFLE, MENU_SIZE };

    enum class PlaylistMenu {
        SHOW,
        CREATE,
        DELETE,
        ADD_SONG,
        REMOVE_SONG,
        GO_BACK,
        MENU_SIZE
    };

    const std::array<std::string, 3> music_status = {
        "Playing", "Paused", "Empty queue"};
};
