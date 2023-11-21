#ifndef MUSICLIBRARY_MUSICLIBRARY_HPP
#define MUSICLIBRARY_MUSICLIBRARY_HPP

#include <algorithm>
#include <filesystem>
#include <future>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "Album.hpp"
#include "FileManager.hpp"
#include "Playlist.hpp"
#include "Song.hpp"

namespace fs = std::filesystem;

class MusicLibrary {
    std::vector<Playlist> allPlaylists;
    std::vector<std::shared_ptr<Song>> allSongs;
    std::unordered_map<std::string, Album> allAlbums;
    // std::vector<Album> allAlbums;
    fs::path directory;

  public:
    MusicLibrary() = default;

    MusicLibrary(fs::path _directory);

    void addPlaylist(const Playlist &playlist);

    template <typename T> void printVector(const std::vector<T> &vec);

    template <typename T> bool isEmpty(std::vector<T> &vector);

    void updateSongs(FileManager &fm);

    void addSongToAlbum(
        const std::string &albumName, const std::shared_ptr<Song> &song);

    void updateAlbums();

    const std::unordered_map<std::string, Album> &getAlbums() const {
        return allAlbums;
    }

    Song getSong(const std::string &songTitle);

    // const std::vector<std::string> getAlbumsName() const;

    std::vector<std::shared_ptr<Song>> &getSongs() { return allSongs; }

    const std::vector<Playlist> &getPlaylists() { return allPlaylists; }

    template <typename T>
    void sortBy(std::vector<T> &vector, bool (*compare)(const T &, const T &)) {
        std::sort(vector.begin(), vector.end(), compare);
    }
};

#endif // MUSICLIBRARY_MUSICLIBRARY_HPP