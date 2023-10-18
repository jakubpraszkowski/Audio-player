#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include "SFML/Audio.hpp"
#include "Song.hpp"
#include <iostream>

class AudioPlayer {
    sf::Music music;

  public:
    AudioPlayer() = default;
    void loadSound2Buffer(const Song &song);
};

#endif // MUSICLIBRARY_AUDIOPLAYER_HPP
