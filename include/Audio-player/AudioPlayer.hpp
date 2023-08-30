#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include <iostream>
#include <filesystem>
#include "SFML/Audio.hpp"
#include "Song.hpp"

namespace fs = std::filesystem;

class AudioPlayer {
    fs::path path, directory;
    sf::Music music;

public:
    AudioPlayer() = default;
    void loadSound2Buffer(const Song &song);
};


#endif //MUSICLIBRARY_AUDIOPLAYER_HPP
