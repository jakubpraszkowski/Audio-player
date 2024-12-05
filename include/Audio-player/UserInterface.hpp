#pragma once

#include <unistd.h>

#include <array>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

#include <ncurses/ncurses.h>

#include "AudioPlayer.hpp"
#include "InputHandler.hpp"
#include "MusicLibrary.hpp"
#include "Playlist.hpp"
#include "Song.hpp"
#include "WindowManager.hpp"

class InputHandler;
struct WinBox;

class UserInterface {
  private:
    enum class Menu;
    enum class PlaylistMenu;

  public:
    using SongsVector = std::vector<std::shared_ptr<Song>>;

    static int get_menu_size();
    static void EntryPoint();

    void
    DrawWindowsOnScreen(MusicLibrary &music_library, AudioPlayer &audio_player);
    void LeftMenuAction(MusicLibrary &music_library, AudioPlayer &audio_player);
    void RefreshWindows();

    ~UserInterface();

    void MoveOnScreenWithKeys(
        MusicLibrary &music_library, AudioPlayer &audio_player, int &ch,
        std::thread &playback_thread);

    void PrintVectorInsideWindow(
        MusicLibrary &music_library, WINDOW *main_win, int &current_line,
        SongsVector &vec);

    template <typename T>
    void PrintVectorInsideWindow(
        MusicLibrary &music_library, WINDOW *win, int &current_line,
        std::vector<T> &vec);

    template <typename T>
    void PrintMenu(
        int &current_line, std::function<std::string(T)> get_menu_option_func);

    void PrintStatus(AudioPlayer &audio_player);
    void PrintProgressBar(AudioPlayer &audio_player);
    void PrintCurrentSong(AudioPlayer &audio_player);
    void InitNcurses();
    void WhichVectorShow(MusicLibrary &music_library);
    void UpdateUi(AudioPlayer &audio_player);
    void StatusThread(AudioPlayer &audio_player);
    void CreatePlaylistMenu(MusicLibrary &music_library);
    void NoPlaylists();
    void PlaylistMenuI();
    void ShowSongs(MusicLibrary &music_library);
    void ShowAlbums(MusicLibrary &music_library);
    void ShowPlaylists(MusicLibrary &music_library);
    void UpdateMenuState();

    std::string get_menu_option(Menu menu);
    std::string get_playlist_menu_option(PlaylistMenu playlist_menu);

  private:
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

    WindowManager window_manager_;
    InputHandler *input_handler_;
    WinBox *win_box_;
    std::array<std::string, 3> music_status = {
        "Playing", "Paused", "Empty queue"};
};
