#ifndef MUSICLIBRARY_PLAYLIST_H
#define MUSICLIBRARY_PLAYLIST_H

#include <string>

class Playlist {
    std::string name, artist;

public:
    Playlist(std::string name);

    const std::string &getName() const;
    void setName(const std::string &name);
    const std::string &getArtist() const;
    void setArtist(const std::string &artist);




};


#endif //MUSICLIBRARY_PLAYLIST_H
