#ifndef MUSICLIBRARY_PLAYLIST_HPP
#define MUSICLIBRARY_PLAYLIST_HPP

#include "Song.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Playlist : public Song {
    std::vector<std::shared_ptr<Song>> playlistSongs;
    std::tm year{};

  public:
    Playlist();

    Playlist(
        std::string title, const std::string &artist,
        const std::vector<std::shared_ptr<Song>> &playlistSongs, std::tm year);

    Playlist createPlaylist();

    static bool compareByDuration(const Playlist &p1, const Playlist &p2);

    static bool compareByTitle(const Playlist &p1, const Playlist &p2);

    static bool compareByCreator(const Playlist &p1, const Playlist &p2);

    static bool compareByYear(const Playlist &p1, const Playlist &p2);

    void addSongToPlaylist(
        const std::shared_ptr<Song> &song, const std::string &playlistTitle,
        std::vector<Song> &playlistSongs);

    void removeSongFromPlaylist(const std::string &songTitle);

    u_int calculateDuration();

    friend std::ostream &operator<<(std::ostream &os, const Playlist &pl);
};

#endif // MUSICLIBRARY_PLAYLIST_HPP
