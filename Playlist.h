#ifndef MUSICLIBRARY_PLAYLIST_H
#define MUSICLIBRARY_PLAYLIST_H

#include <string>
#include <vector>
#include "Song.h"

class Playlist : public Song{
    std::vector<Song> playlistSongs;

public:
    Playlist() = default;
    Playlist(std::string title);
    Playlist(std::string title, std::string artist);
    Playlist createPlaylist();

    bool operator<(const Playlist& p1) const;

    void addSongToPlaylist(const Song& song);
    void removeSongFromPlaylist(const std::string& songTitle);

};


#endif //MUSICLIBRARY_PLAYLIST_H
