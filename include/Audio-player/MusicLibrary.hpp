#ifndef MUSICLIBRARY_MUSICLIBRARY_HPP
#define MUSICLIBRARY_MUSICLIBRARY_HPP

#include <algorithm>
#include <filesystem>
#include <future>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

#include "Album.hpp"
#include "FileManager.hpp"
#include "Playlist.hpp"
#include "Song.hpp"

namespace fs = std::filesystem;

class MusicLibrary {
    std::vector<Playlist> allPlaylists;
    std::vector<Song> allSongs;
    std::vector<Album> allAlbums;
    std::map<std::string, std::vector<Song>> albums;
    fs::path directory;

  public:
    MusicLibrary() = default;
    MusicLibrary(fs::path _directory);
    void addSong(const Song &song);
    void addPlaylist(const Playlist &playlist);

    template <typename T> void printVector(const std::vector<T> &vec);

    std::vector<Song> &getSongs() { return allSongs; }
    // std::vector<Album> &getAlbums() { return allAlbums; }
    std::vector<std::string> getAlbumsName();
    std::vector<Playlist> &getPlaylists() { return allPlaylists; }

    Song getSong(const std::string &songTitle);

    template <typename T> bool isEmpty(std::vector<T> &vector);

    template <typename T>
    void sortBy(std::vector<T> &vector, bool (*compare)(const T &, const T &)) {
        std::sort(vector.begin(), vector.end(), compare);
    }

    void updateSongs(FileManager &fm);
};

#endif // MUSICLIBRARY_MUSICLIBRARY_HPP