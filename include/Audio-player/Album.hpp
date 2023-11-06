#ifndef MUSICLIBRARY_ALBUM_HPP
#define MUSICLIBRARY_ALBUM_HPP

#include "Song.hpp"
#include <vector>

class Album : Song {
    std::vector<Song> songsPerAlbum;

  public:
    Album(std::string album);
    void addSong(const Song &song);
    std::vector<Song> &getSongs() const { return songsPerAlbum; }
    void printAlbumSongs();
};

#endif // MUSICLIBRARY_ALBUM_HPP
