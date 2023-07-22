#ifndef MUSICLIBRARY_PLAYLIST_H
#define MUSICLIBRARY_PLAYLIST_H

#include <string>
#include <vector>
#include "Song.h"

class Playlist : public Song{
    std::vector<Song> playlistSongs;

public:
    Playlist(std::string title);
    void createPlaylist();
//
//    int getDuration() const;
//    void setDuration(int duration);
//    std::string getName() const;
//    void setName(const std::string &name);
//    std::string getArtist() const;
//    void setArtist(const std::string &artist);



};


#endif //MUSICLIBRARY_PLAYLIST_H
