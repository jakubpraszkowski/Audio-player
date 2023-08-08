#include "../include/Audio-player/Playlist.hpp"
#include <utility>

Playlist Playlist::createPlaylist() {
    std::cout << "Enter the title of the playlist: ";
    std::cin >> creator;
    Playlist p1(name, creator, playlistSongs);
    return p1;
}

Playlist::Playlist(std::string name, const std::string& creator, const std::vector<std::shared_ptr<Song>>& playlistSongs) {
    this->name = name;

    char* envUsername = std::getenv("USERNAME");
    if(envUsername != nullptr) {
        this->creator = envUsername;
    } else {
        this->creator = "Unknown";
    }

    this->playlistSongs = playlistSongs;
}

bool Playlist::compareByDuration(const Playlist &p1, const Playlist &p2) {
    return p1.duration < p2.duration;
}

bool Playlist::compareByTitle(const Playlist &p1, const Playlist &p2) {
    return p1.name < p2.name;
}

bool Playlist::compareByCreator(const Playlist &p1, const Playlist &p2) {
    return p1.creator < p2.creator;
}

bool Playlist::compareByYear(const Playlist &p1, const Playlist &p2) {
    return p1.year < p2.year;
}

void Playlist::addSongToPlaylist(const Song &song, std::string playlistTitle, std::vector<Song> playlistSongs) {
    playlistSongs.push_back(song);
    std::cout << "Song " << song.getTitle() << " added to playlist " << playlistTitle << std::endl;
}

void Playlist::removeSongFromPlaylist(const std::string &songTitle) {
    for (auto & playlistSong : playlistSongs) {
        if (playlistSong->getTitle() == songTitle) {
            playlistSongs.erase(playlistSongs.begin());
            std::cout << "Song " << songTitle << " removed from playlist " << name << std::endl;
        }
    }
}
