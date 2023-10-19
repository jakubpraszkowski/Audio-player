#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include "MusicLibrary.hpp"
#include "Song.hpp"
#include <SFML/Audio.hpp>
#include <atomic>
#include <deque>
#include <iostream>

class AudioPlayer {
    sf::Music music;
    std::deque<Song> songQueue;

  public:
    AudioPlayer() = default;
    void loadSound2Queue(int &whichItem, std::vector<Song> &vec);
    void playQueue();
};

#endif // MUSICLIBRARY_AUDIOPLAYER_HPP