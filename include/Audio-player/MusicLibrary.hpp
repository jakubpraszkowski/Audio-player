#ifndef MUSICLIBRARY_MUSICLIBRARY_HPP
#define MUSICLIBRARY_MUSICLIBRARY_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include "Playlist.hpp"
#include "Song.hpp"
#include "Album.hpp"

class MusicLibrary {
    std::vector<Playlist> playlists;
    std::vector<Song> songs;

public:
    MusicLibrary() = default;
    void addSong(const Song& song);
    void addPlaylist(const Playlist& playlist);
    void print();

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