#include "Playlist.h"

#include <utility>

Playlist Playlist::createPlaylist() {
    std::cout << "Enter the title of the playlist: ";
    std::cin >> title;
    Playlist p1(title, artist, playlistSongs);
    return p1;
}

Playlist::Playlist(std::string title, const std::string& artist, std::vector<Song> playlistSongs) {
    this->title = std::move(title);

    char* envUsername = std::getenv("USERNAME");
    if(envUsername != nullptr) {
        this->artist = envUsername;
    } else {
        this->artist = "Unknown";
    }

    this->playlistSongs = std::move(playlistSongs);
}

bool Playlist::compareByDuration(const Playlist &p1, const Playlist &p2) {
    return p1.duration < p2.duration;
}

bool Playlist::compareByTitle(const Playlist &p1, const Playlist &p2) {
    return p1.title < p2.title;
}

bool Playlist::compareByCreator(const Playlist &p1, const Playlist &p2) {
    return p1.artist < p2.artist;
}

bool Playlist::compareByYear(const Playlist &p1, const Playlist &p2) {
    return p1.year < p2.year;
}
