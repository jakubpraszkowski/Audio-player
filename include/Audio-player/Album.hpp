#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_ALBUM_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_ALBUM_HPP

#include <memory>
#include <vector>

#include "Song.hpp"

class Album : Song {
  public:
    Album() = default;

    Album(const std::string name);

    std::vector<std::shared_ptr<Song>> &getAlbumSongs();

    const std::string &getAlbumName() const { return name; }

    void addSong(std::shared_ptr<Song> song);

  private:
    std::vector<std::shared_ptr<Song>> songsInAlbum;
};

#endif // MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_ALBUM_HPP