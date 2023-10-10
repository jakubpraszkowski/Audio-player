#ifndef MUSICLIBRARY_MUSICLIBRARY_HPP
#define MUSICLIBRARY_MUSICLIBRARY_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <filesystem>

#include "FileManager.hpp"
#include "Playlist.hpp"
#include "Song.hpp"
#include "Album.hpp"

namespace fs = std::filesystem;

class MusicLibrary
{
    std::vector<Playlist> playlists;
    std::vector<Song> songs;
    std::vector<Album> albums;
    fs::path directory;

public:
    MusicLibrary() = default;
    MusicLibrary(fs::path _directory);
    void addSong(const Song &song);
    void addPlaylist(const Playlist &playlist);

    template <typename T>
    void printVector(const std::vector<T> &vec);

    std::vector<Song> &getSongs() { return songs; }
    std::vector<Album> &getAlbums() { return albums; }
    std::vector<Playlist> &getPlaylists() { return playlists; }

    Song getSong(const std::string &songTitle);

    template <typename T>
    bool isEmpty(std::vector<T> &vector);

    template <typename T>
    void sortBy(std::vector<T> &vector, bool (*compare)(const T &, const T &))
    {
        std::sort(vector.begin(), vector.end(), compare);
    }

    void updateSongs(FileManager &fm);
};

#endif // MUSICLIBRARY_MUSICLIBRARY_HPP