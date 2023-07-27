#ifndef MUSICLIBRARY_MUSICLIBRARY_H
#define MUSICLIBRARY_MUSICLIBRARY_H

#include <vector>
#include <iostream>
#include <type_traits>
#include "Playlist.h"

class MusicLibrary {
    std::vector<Playlist> playlists;
    std::vector<Song> songs;
    enum sortCriteria {
        DURATION,
        TITLE,
    };

    sortCriteria criteria;

public:
    MusicLibrary() = default;
    void addSong(const Song& song);
    void addPlaylist(const Playlist& playlist);
    void print();

    template <typename T>
    void removeItem(const std::string &itemTitle);

    template <typename T>
    bool isEmpty(std::vector<T> &vector);

    //double calculateDurationPlaylist();

    template <typename T>
    void sortItem(std::vector<T>& vector, sortCriteria sortCriteria);

    std::vector<Playlist> getPlaylistVector();
    std::vector<Song> getSongVector();

    sortCriteria getSortCriteria() const;


    void sortByAlbum();
};

#endif //MUSICLIBRARY_MUSICLIBRARY_H