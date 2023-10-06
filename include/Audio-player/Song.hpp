#ifndef MUSICLIBRARY_SONG_HPP
#define MUSICLIBRARY_SONG_HPP

#include <string>
#include <iostream>
#include "MusicItem.hpp"

class Song : public MusicItem
{
    std::string album;
    std::string genre;
    u_int year = 0;
    std::string path;

public:
    Song() = default;

    Song(std::string title, std::string artist, std::string album, std::string genre,
         u_int year, int duration, std::string path);

    Song(std::string title, int duration);

    u_int calculateDuration() override;

    u_int getYear();

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    const std::string &getArtist() const;

    void setArtist(const std::string &artist);

    const std::string &getAlbum() const;

    void setAlbum(const std::string &album);

    const std::string &getGenre() const;

    void setGenre(const std::string &genre);

    u_int getYear() const;

    void setYear(u_int year);

    int getDuration() const;

    void setDuration(int duration);

    void setPath(const std::string &path);

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
