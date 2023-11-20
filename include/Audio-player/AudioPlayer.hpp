#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include "MusicLibrary.hpp"
#include "Song.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <atomic>
#include <deque>
#include <iostream>

class AudioPlayer {
    sf::Music music;
    std::deque<std::shared_ptr<Song>> songQueue;
    std::mutex musicMutex;
    sf::Time currentTime;

  public:
    AudioPlayer() = default;

    void
    loadSound2Queue(int &whichItem, std::vector<std::shared_ptr<Song>> &vec);

    void playQueue();

    bool isDequeEmpty();

    sf::Music &getCurrentMusic();

    bool checkMusicPlaying();

    void pauseOrResumeMusic(sf::Music &music);

    void advanceForwardMusic(sf::Music &music);

    void advanceBackwardMusic(sf::Music &music);

    void stopMusic(sf::Music &music);

    sf::Time &getCurrentTime();

    float calculateSongProgressBar(sf::Music &music);
};

#endif // MUSICLIBRARY_AUDIOPLAYER_HPP