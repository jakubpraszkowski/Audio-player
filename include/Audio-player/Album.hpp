#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Song.hpp"

class Album : public Song {
  public:
  using SongsVector = std::vector<std::shared_ptr<Song>>;

    Album() = default;

    Album(const std::string &album_name);

    SongsVector &get_album_songs();

    void add_song(std::shared_ptr<Song> song);

  private:
    SongsVector songs_in_album_;
};
