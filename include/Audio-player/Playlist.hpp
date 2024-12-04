#pragma once

#include <chrono>
#include <ctime>
#include <memory>
#include <string>
#include <vector>

#include "Song.hpp"

class Playlist : public Song {
  public:
    using SongsVector = std::vector<std::shared_ptr<Song>>;

    Playlist() = default;
    explicit Playlist(const std::string &title);
    Playlist(
        const std::string &title, const std::string &artist,
        SongsVector &playlist_songs);

    Playlist(const Playlist &other_playlist);
    Playlist &operator=(const Playlist &other_playlist);
    ~Playlist() = default;

    void AddSongToPlaylist(
        const std::shared_ptr<Song> &song, const std::string &playlist_title,
        std::vector<Song> &playlist_songs);

    void RemoveSongFromPlaylist(const std::string &song_title);
    unsigned int CalculateDuration();

    static bool CompareByDuration(const Playlist &p1, const Playlist &p2);
    static bool CompareByTitle(const Playlist &p1, const Playlist &p2);
    static bool CompareByCreator(const Playlist &p1, const Playlist &p2);
    static bool CompareByYear(const Playlist &p1, const Playlist &p2);

  private:
    SongsVector playlist_songs_;
    std::tm year_;
};
