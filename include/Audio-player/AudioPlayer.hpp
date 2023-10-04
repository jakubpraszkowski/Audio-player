#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include <iostream>
#include "SFML/Audio.hpp"
#include "Song.hpp"

class AudioPlayer
{
    sf::Music music;

public:
    AudioPlayer() = default;
    void loadSound2Buffer(const Song &song);
};

#endif // MUSICLIBRARY_AUDIOPLAYER_HPP
