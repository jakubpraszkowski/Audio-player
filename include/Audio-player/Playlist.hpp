#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_PLAYLIST_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_PLAYLIST_HPP

#include <chrono>
#include <ctime>
#include <memory>
#include <vector>

#include "Song.hpp"

class Playlist : public Song {
  public:
    Playlist();

    Playlist(
        std::string title, const std::string &artist,
        std::vector<std::shared_ptr<Song>> &playlistSongs, std::tm year);

    Playlist createPlaylist();

    bool compareByDuration(const Playlist &p1, const Playlist &p2);

    bool compareByTitle(const Playlist &p1, const Playlist &p2);

    bool compareByCreator(const Playlist &p1, const Playlist &p2);

    bool compareByYear(const Playlist &p1, const Playlist &p2);

    void addSongToPlaylist(
        const std::shared_ptr<Song> &song, const std::string &playlistTitle,
        std::vector<Song> &playlistSongs);

    void removeSongFromPlaylist(const std::string &songTitle);

    u_int calculateDuration();

  private:
    std::vector<std::shared_ptr<Song>> playlistSongs;
    std::tm year{};
};

#endif // MUSICLIBRARY_PLAYLIST_HPP
