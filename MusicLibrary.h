#ifndef MUSICLIBRARY_MUSICLIBRARY_H
#define MUSICLIBRARY_MUSICLIBRARY_H

#include <vector>
#include <iostream>
#include "Song.h"
#include "Playlist.h"

template <typename T>
class MusicLibrary {
    std::vector<Playlist> playlists;
    std::vector<Song> songs;

public:
    MusicLibrary() = default;
    void addSong(Song& song);
    void addPlaylist(Playlist& playlist);
    void removeSong(Song& song);
    void removePlaylist(Playlist& playlist);
    void print();
    bool isEmpty(std::vector<T> &vector);

    double calculateDurationPlaylist();

    static bool compareByName(const T& t1, const T& t2);
    static bool compareByCreator(const T& t1, const T& t2);
    static bool compareByGenre(const Song& s1, const Song& s2);
    static bool compareByYear(const T& t1, const T& t2);
    static bool compareByDuration(const T& t1, const T& t2);
    static bool compareByAlbum(const Song& s1, const Song& s2);

    void sortByCreator();
    void sortByName();
    void sortByGenre();
    void sortByYear();
    void sortByDuration();
    void sortByAlbum();
};


#endif //MUSICLIBRARY_MUSICLIBRARY_H
