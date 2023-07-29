#include "Playlist.h"
#include <utility>

Playlist Playlist::createPlaylist() {
    std::cout << "Enter the title of the playlist: ";
    std::cin >> title;
    Playlist p1(title, artist, playlistSongs);
    return p1;
}

Playlist::Playlist(std::string title, const std::string& artist, const std::vector<std::shared_ptr<Song>>& playlistSongs) {
    this->title = std::move(title);

    char* envUsername = std::getenv("USERNAME");
    if(envUsername != nullptr) {
        this->artist = envUsername;
    } else {
        this->artist = "Unknown";
    }

    this->playlistSongs = playlistSongs;
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

void Playlist::addSongToPlaylist(const Song &song, std::string playlistTitle, std::vector<Song> playlistSongs) {
    playlistSongs.push_back(song);
    std::cout << "Song " << song.getTitle() << " added to playlist " << playlistTitle << std::endl;
}