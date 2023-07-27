#include "Playlist.h"

Playlist::Playlist(std::string title) {
    this->title = title;
}

Playlist Playlist::createPlaylist() {
    std::cout << "Enter the title of the playlist: ";
    std::cin >> title;
    Playlist p1(title);
    return p1;
}

Playlist::Playlist(std::string title, std::string artist) {
    this->title = title;
    this->artist = artist;
}

bool Playlist::compareByDuration(const Playlist &p1, const Playlist &p2) {
    return p1.duration < p2.duration;
}

bool Playlist::compareByTitle(const Playlist &p1, const Playlist &p2) {
    return p1.title < p2.title;
}

bool Playlist::compareByArtist(const Playlist &p1, const Playlist &p2) {
    return p1.artist < p2.artist;
}

bool Playlist::compareByYear(const Playlist &p1, const Playlist &p2) {
    return p1.year < p2.year;
}
