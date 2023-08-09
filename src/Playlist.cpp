#include "../include/Audio-player/Playlist.hpp"

Playlist Playlist::createPlaylist() {
    std::cout << "Enter the title of the playlist: ";
    std::cin >> name;
    Playlist p1(name, creator, playlistSongs, year);
    return p1;
}

Playlist::Playlist(std::string name, const std::string& creator, const std::vector<std::shared_ptr<Song>>& playlistSongs, std::tm year) {
    this->name = name;

    char* envUsername = std::getenv("USERNAME");
    if(envUsername != nullptr) {
        this->creator = envUsername;
    } else {
        this->creator = "Unknown";
    }

    this->playlistSongs = playlistSongs;

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    year = *std::localtime(&now_time);
    this->year = year;

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
    std::tm tm1 = p1.year;
    std::tm tm2 = p2.year;

    if (tm1.tm_year != tm2.tm_year) {
        return tm1.tm_year < tm2.tm_year;
    } else if (tm1.tm_mon != tm2.tm_mon) {
        return tm1.tm_mon < tm2.tm_mon;
    } else {
        return tm1.tm_mday < tm2.tm_mday;
    }
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

u_int Playlist::calculateDuration() {
    u_int duration = 0;
    for(const auto& song : playlistSongs) {
        duration += song->getDuration();
    }
    return duration;
}

std::ostream &operator<<(std::ostream &os, const Playlist &pl){
    os << "Title: " << pl.name << " Artist: " << pl.creator << " Year: " << std::put_time(&pl.year, "%Y-%m-%d %H:%M:%S") << " Duration: " << pl.duration;
    return os;
}
