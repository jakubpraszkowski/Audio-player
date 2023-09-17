#ifndef MUSICLIBRARY_MUSICLIBRARY_HPP
#define MUSICLIBRARY_MUSICLIBRARY_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <filesystem>

#include "Playlist.hpp"
#include "Song.hpp"
#include "Album.hpp"

namespace fs = std::filesystem;

class MusicLibrary {
    std::vector<Playlist> playlists;
    std::vector<Song> songs;
    std::vector<Album> albums;
    fs::path directory;

public:
    MusicLibrary() = default;
    MusicLibrary(fs::path _directory);
    void addSong(const Song& song);
    void addPlaylist(const Playlist& playlist);

    template <typename T>
    void printVector(const std::vector<T> &vec);

//    template <typename T>
//    void removeItem(const std::string &itemTitle);

    template <typename T>
    std::vector<T>& getVector();

    template <typename T>
    bool isEmpty(std::vector<T> &vector);

    template <typename T>
    void sortBy(std::vector<T>& vector, bool(*compare)(const T&, const T&)) {
        std::sort(vector.begin(), vector.end(), compare);
    }

    template <typename T>
    std::vector<T>& getItem();
};

#endif //MUSICLIBRARY_MUSICLIBRARY_HPP