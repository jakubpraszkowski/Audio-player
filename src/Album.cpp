#include "../include/Audio-player/Album.hpp"

Album::Album(const std::string name) { this->name = name; }

std::vector<std::shared_ptr<Song>> &Album::getAlbumSongs() {
    return songsInAlbum;
}

void Album::addSong(std::shared_ptr<Song> song) {
    songsInAlbum.push_back(song);
}

void Album::printAlbumSongs() {
    for (const auto &song : songsInAlbum) {
        std::cout << song->getTitle() << std::endl;
    }
}