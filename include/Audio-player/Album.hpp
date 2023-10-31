#ifndef MUSICLIBRARY_ALBUM_HPP
#define MUSICLIBRARY_ALBUM_HPP

#include "Song.hpp"

class Album : Song {
  public:
    u_int calculateDuration();
};

#endif // MUSICLIBRARY_ALBUM_HPP
