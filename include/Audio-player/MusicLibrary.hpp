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
    void addSong(const Song& song);
    void addPlaylist(const Playlist& playlist);
    void print();

    void findOggFiles(const fs::path &_directory, std::vector<std::string>& oggFiles);


//    template <typename T>
//    void removeItem(const std::string &itemTitle);

    template <typename T>
    bool isEmpty(std::vector<T> &vector);

    template <typename T>
    void sortBy(std::vector<T>& vector, bool(*compare)(const T&, const T&)) {
        std::sort(vector.begin(), vector.end(), compare);
    }

    std::vector<Playlist>& getPlaylists();
    std::vector<Song>& getSongs();
};

#endif //MUSICLIBRARY_MUSICLIBRARY_HPP