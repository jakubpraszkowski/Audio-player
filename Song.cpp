#include "Song.h"

Song::Song(std::string title, std::string artist, std::string album, std::string genre,
           int year, int duration) : title(title), artist(artist), album(album), genre(genre), year(year),
                                     duration(duration) {}

const std::string &Song::getTitle() const{
    return title;
}

void Song::setTitle(const std::string &title) {
    Song::title = title;
}

const std::string &Song::getArtist() const {
    return artist;
}

void Song::setArtist(const std::string &artist) {
    Song::artist = artist;
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

int Song::getYear() const {
    return year;
}

void Song::setYear(int year) {
    Song::year = year;
}

int Song::getDuration() const {
    return duration;
}

void Song::setDuration(int duration) {
    Song::duration = duration;
}

std::ostream &operator<<(std::ostream &os, const Song &song) {
os << "Title: " << song.title << " Artist: " << song.artist << " Album: " << song.album << " Genre: " << song.genre
       << " Year: " << song.year << " Duration: " << song.duration;
    return os;
}

Song Song::createSong() {
    std::cout << "Enter the title of the song: ";
    std::cin >> title;
    std::cout << "Enter the artist of the song: ";
    std::cin >> artist;
    std::cout << "Enter the album of the song: ";
    std::cin >> album;
    std::cout << "Enter the genre of the song: ";
    std::cin >> genre;
    std::cout << "Enter the year of the song: ";
    std::cin >> year;
    std::cout << "Enter the duration of the song: ";
    std::cin >> duration;

    Song s1(title, artist, album, genre, year, duration);
    return s1;
}
