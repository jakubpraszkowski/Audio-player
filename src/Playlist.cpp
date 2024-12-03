#include "../include/Audio-player/Playlist.hpp"

Playlist::Playlist(
    const std::string &title, const std::string &creator,
    SongsVector &playlist_songs, std::tm year) {
    title_ = title;

    char *env_username = std::getenv("USERNAME");
    if (env_username != nullptr) {
        artist_ = env_username;
    } else {
        artist_ = "Unknown";
    }

    playlist_songs_ = playlist_songs;

    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    year = *std::localtime(&now_time);
    year_ = year;
}

Playlist::Playlist(const std::string &title) { title_ = title; }

Playlist::Playlist(const Playlist &other_playlist)
    : playlist_songs_(other_playlist.playlist_songs_) {
    std::copy(
        other_playlist.playlist_songs_.begin(), other_playlist.playlist_songs_.end(),
        playlist_songs_.begin());
    artist_ = other_playlist.artist_;
    artist_ = other_playlist.artist_;
    year_ = other_playlist.year_;
}

Playlist &Playlist::operator=(const Playlist &other_playlist) {
    if (this == &other_playlist) {
        return *this;
    }
    std::copy(
        other_playlist.playlist_songs_.begin(), other_playlist.playlist_songs_.end(),
        playlist_songs_.begin());
    artist_ = other_playlist.artist_;
    artist_ = other_playlist.artist_;
    year_ = other_playlist.year_;

    return *this;
}

bool Playlist::CompareByDuration(const Playlist &p1, const Playlist &p2) {
    return p1.duration_ < p2.duration_;
}

bool Playlist::CompareByTitle(const Playlist &p1, const Playlist &p2) {
    return p1.artist_ < p2.artist_;
}

bool Playlist::CompareByCreator(const Playlist &p1, const Playlist &p2) {
    return p1.artist_ < p2.artist_;
}

bool Playlist::CompareByYear(const Playlist &p1, const Playlist &p2) {
    std::tm tm1 = p1.year_;
    std::tm tm2 = p2.year_;

    if (tm1.tm_year != tm2.tm_year) {
        return tm1.tm_year < tm2.tm_year;
    } else if (tm1.tm_mon != tm2.tm_mon) {
        return tm1.tm_mon < tm2.tm_mon;
    } else {
        return tm1.tm_mday < tm2.tm_mday;
    }
}

void Playlist::AddSongToPlaylist(
    const std::shared_ptr<Song> &song, const std::string &playlist_title,
    std::vector<Song> &playlist_songs) {
    playlist_songs_.push_back(song);
}

void Playlist::RemoveSongFromPlaylist(const std::string &song_title) {
    for (auto &playlist_song : playlist_songs_) {
        if (playlist_song->get_title() == song_title) {
            playlist_songs_.erase(playlist_songs_.begin());
        }
    }
}

unsigned int Playlist::CalculateDuration() {
    unsigned int duration = 0;
    for (const auto &song : playlist_songs_) {
        duration += song->get_duration();
    }
    return duration;
}