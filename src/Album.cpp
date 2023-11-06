#include "../include/Audio-player/Album.hpp"

Album::Album(std::string album) { this->album = album; }

void Album::addSong(const Song &song) { songsPerAlbum.push_back(song); }

void Album::printAlbumSongs() {
    for (const auto &song : songsPerAlbum) {
        std::cout << song << std::endl;
    }
}