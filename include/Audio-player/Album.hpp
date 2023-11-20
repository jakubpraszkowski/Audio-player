#pragma once
#include "Song.hpp"
#include <memory>
#include <vector>

class Album : Song {
    std::vector<std::shared_ptr<Song>> songsInAlbum;

  public:
    Album() = default;

    Album(const std::string name);

    std::vector<std::shared_ptr<Song>> &getAlbumSongs();

    void addSong(std::shared_ptr<Song> song);
};