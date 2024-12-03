#include "../include/Audio-player/Album.hpp"

Album::Album(const std::string &album_name) { album_ = album_name;}

Album::SongsVector &Album::get_album_songs() { return songs_in_album_; }

void Album::add_song(std::shared_ptr<Song> song) {
    songs_in_album_.push_back(song);
}