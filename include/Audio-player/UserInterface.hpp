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
    enum class Menu;
    enum class PlaylistMenu;

  public:
    using SongsVector = std::vector<std::shared_ptr<Song>>;

    static void EntryPoint();

    void
    DrawWindowsOnScreen(MusicLibrary &music_library, AudioPlayer &audio_player);

    void CreateWindows();

    void RefreshWindows();

    void MoveOnScreenWithKeys(
        MusicLibrary &music_library, AudioPlayer &audio_player, int &ch,
        std::thread &playback_thread);

    void HandleF4Key(
        MusicLibrary &music_library, AudioPlayer &audio_player,
        std::thread &playback_thread);

    void PrintVectorInsideWindow(
        MusicLibrary &music_library, WINDOW *main_win, int &current_line,
        SongsVector &vec);

    template <typename T>
    void PrintVectorInsideWindow(
        MusicLibrary &music_library, WINDOW *win, int &current_line,
        std::vector<T> &vec);

    template <typename T> void MoveDown(std::vector<T> &vec, int &current_line);

    void MoveDown(int &current_line, std::function<int()> get_size_func);

    void MoveUp(int &current_line);

    template <typename T>
    void PrintMenu(
        int &current_line, std::function<std::string(T)> get_menu_option_func);

    void PrintStatus(AudioPlayer &audio_player);

    void PrintProgressBar(AudioPlayer &audio_player);

    void PrintCurrentSong(AudioPlayer &audio_player);

    void InitNcurses();

    void ProcessKeyUp();

    void ProcessKeyDown(MusicLibrary &music_library);

    void LeftMenuAction(MusicLibrary &music_library, AudioPlayer &audio_player);

    void WhichVectorShow(MusicLibrary &music_library);

    void UpdateUi(AudioPlayer &audio_player);

    void StatusThread(AudioPlayer &audio_player);

    void CreatePlaylistMenu(MusicLibrary &music_library);

    std::string get_menu_option(Menu menu);

    std::string get_playlist_menu_option(PlaylistMenu playlist_menu);

    void NoPlaylists();

    void PlaylistMenuI();

  private:
    struct WinBox {
        int current_line_1st_box = 0;
        int current_line_3rd_box = 0;
        int current_box = 2;
    } win_box_;

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
        WINDOW *sidebar_win = nullptr;
        WINDOW *top_win = nullptr;
        WINDOW *main_win = nullptr;
    } window_init_;

    struct MenuBool {
        bool is_song_menu = false;
        bool is_album_menu = false;
        bool is_playlist_menu = false;
    } menu_bool_;

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
