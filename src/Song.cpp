#include "../include/Audio-player/Song.hpp"

Song::Song(
    const std::string &title, const std::string &artist,
    const std::string &album, const std::string &genre, unsigned int year,
    int duration, const std::string &path) {
    title_ = title;
    artist_ = artist;
    album_ = album;
    genre_ = genre;
    year_ = year;
    duration_ = duration;
    path_ = path;
}

Song::Song(const std::string &title, const std::string &file_path, int duration)
    : title_(title), path_(file_path), duration_(duration) {}

Song::Song(const std::string &title, int duration) {
    title_ = title;
    duration_ = duration;
}

const std::string &Song::get_title() const { return title_; }

const std::string &Song::get_artist() const { return artist_; }

const std::string &Song::get_album() const { return album_; }

const std::string &Song::get_genre() const { return genre_; }

unsigned int Song::get_year() const { return year_; }

int Song::get_duration() const { return duration_; }

const std::string &Song::get_path() const { return path_; }

bool Song::CompareByDuration(const Song &s1, const Song &s2) {
    return s1.duration_ < s2.duration_;
}

bool Song::CompareByTitle(const Song &s1, const Song &s2) {
    return s1.title_ < s2.title_;
}

bool Song::CompareByArtist(const Song &s1, const Song &s2) {
    return s1.artist_ < s2.artist_;
}

bool Song::CompareByAlbum(const Song &s1, const Song &s2) {
    return s1.album_ < s2.album_;
}

bool Song::CompareByGenre(const Song &s1, const Song &s2) {
    return s1.genre_ < s2.genre_;
}

bool Song::CompareByYear(const Song &s1, const Song &s2) {
    return s1.year_ < s2.year_;
}
