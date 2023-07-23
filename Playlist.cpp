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
