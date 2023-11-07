#ifndef MUSICLIBRARY_ALBUM_HPP
#define MUSICLIBRARY_ALBUM_HPP

#include "Song.hpp"
#include <string>
#include <vector>

class Album : Song {
    std::vector<Song> songsPerAlbum;

  public:
    Album() = default;
    Album(std::string album);
    void addSong(const Song &song);
    std::vector<Song> &getSongs() { return songsPerAlbum; }
    void printAlbumSongs();

    std::string &getAlbumName() { return album; }
};

#endif // MUSICLIBRARY_ALBUM_HPP
