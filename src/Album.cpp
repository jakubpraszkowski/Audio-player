#include "../include/Audio-player/Album.hpp"

Album::Album(const std::string &album_name) { name = album_name; }

std::vector<std::shared_ptr<Song>> &Album::getAlbumSongs() {
    return songsInAlbum;
}

const std::string &Album::getAlbumName() const { return name; }

void Album::addSong(std::shared_ptr<Song> song) {
    songsInAlbum.push_back(song);
}