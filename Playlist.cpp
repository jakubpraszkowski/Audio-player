#include "Playlist.h"

const std::string &Playlist::getName() const {
    return name;
}

void Playlist::setName(const std::string &name) {
    Playlist::name = name;
}

Playlist::Playlist(std::string name) {
    this->name = name;
}

const std::string &Playlist::getArtist() const {
    return artist;
}

void Playlist::setArtist(const std::string &artist) {
    Playlist::artist = artist;
}
