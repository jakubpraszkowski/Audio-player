#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include "Song.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <queue>

class AudioPlayer {
    sf::Music music;
    std::queue<Song> songQueue;

  public:
    AudioPlayer() = default;

    template <typename T>
    void loadSound2Queue(const T sound, const std::vector<T> &vec);

    // template <typename T> void loadVector2Buffer(const std::vector<T> &vec);
};

#endif // MUSICLIBRARY_AUDIOPLAYER_HPP
