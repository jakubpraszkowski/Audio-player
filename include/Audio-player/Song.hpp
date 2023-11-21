#ifndef MUSICLIBRARY_SONG_HPP
#define MUSICLIBRARY_SONG_HPP

#include <iostream>
#include <memory>
#include <string>

class Song {
    std::string genre;
    u_int year = 0;
    std::string path;

  protected:
    std::string name;
    std::string creator;
    u_int size;
    u_int duration;
    std::string album;

  public:
    Song() = default;

    Song(
        std::string title, std::string artist, std::string album,
        std::string genre, u_int year, int duration, std::string path);

    Song(std::string title, int duration);

    const std::string &getTitle() const;

    const std::string &getArtist() const;

    const std::string &getAlbum() const;

    const std::string &getGenre() const;

    const u_int getYear() const;

    const int getDuration() const;

    const std::string &getPath() const;

    friend std::ostream &operator<<(std::ostream &os, const Song &song);

    static bool compareByDuration(const Song &s1, const Song &s2);

    static bool compareByTitle(const Song &s1, const Song &s2);

    static bool compareByArtist(const Song &s1, const Song &s2);

    static bool compareByAlbum(const Song &s1, const Song &s2);

    static bool compareByGenre(const Song &s1, const Song &s2);

    static bool compareByYear(const Song &s1, const Song &s2);
};

#endif // MUSICLIBRARY_SONG_HPP
