#include "../include/Audio-player/Song.hpp"

Song::Song(std::string name, std::string creator, std::string album, std::string genre,
           u_int year, int duration) {
    this->name = name;
    this->creator = creator;
    this->album = album;
    this->genre = genre;
    this->year = year;
    this->duration = duration;
}

const std::string &Song::getTitle() const {
    return name;
}

void Song::setTitle(const std::string &title) {
    Song::name = title;
}

const std::string &Song::getArtist() const {
    return creator;
}

void Song::setArtist(const std::string &artist) {
    Song::creator = artist;
}

const std::string &Song::getAlbum() const {
    return album;
}

void Song::setAlbum(const std::string &album) {
    Song::album = album;
}

const std::string &Song::getGenre() const {
    return genre;
}

void Song::setGenre(const std::string &genre) {
    Song::genre = genre;
}

u_int Song::getYear() const {
    return year;
}

void Song::setYear(u_int year) {
    Song::year = year;
}

int Song::getDuration() const {
    return duration;
}

void Song::setDuration(int duration) {
    Song::duration = duration;
}

std::ostream &operator<<(std::ostream &os, const Song &song) {
    os << "Title: " << song.name << " Artist: " << song.creator << " Album: " << song.album << " Genre: " << song.genre
       << " Year: " << song.year << " Duration: " << song.duration;
    return os;
}

Song Song::createSong() {
    std::cout << "Enter the title of the song: ";
    std::cin >> name;
    std::cout << "Enter the artist of the song: ";
    std::cin >> creator;
    std::cout << "Enter the album of the song: ";
    std::cin >> album;
    std::cout << "Enter the genre of the song: ";
    std::cin >> genre;
    std::cout << "Enter the year of the song: ";
    std::cin >> year;
    std::cout << "Enter the duration of the song: ";
    std::cin >> duration;
    Song s1(name, creator, album, genre, year, duration);
    return s1;
}

bool Song::compareByDuration(const Song &s1, const Song &s2) {
    return s1.duration < s2.duration;
}

bool Song::compareByTitle(const Song &s1, const Song &s2) {
    return s1.name < s2.name;
}

bool Song::compareByArtist(const Song &s1, const Song &s2) {
    return s1.creator < s2.creator;
}

bool Song::compareByAlbum(const Song &s1, const Song &s2) {
    return s1.album < s2.album;
}

bool Song::compareByGenre(const Song &s1, const Song &s2) {
    return s1.genre < s2.genre;
}

bool Song::compareByYear(const Song &s1, const Song &s2) {
    return s1.year < s2.year;
}

u_int Song::calculateDuration() {
    return 0;
}

u_int Song::getYear() {
    return 0;
}
