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
    std::deque<Song> songQueue;
    std::mutex musicMutex;
    sf::Time currentTime;

  public:
    AudioPlayer() = default;
    void loadSound2Queue(int &whichItem, std::vector<Song> &vec);
    void loadSound2Queue(std::vector<Song> &vec);
    bool isDequeEmpty();
    void playQueue();
    sf::Music &getCurrentMusic();
    void advanceForwardMusic(sf::Music &music);
    void advanceBackwardMusic(sf::Music &music);
    void stopMusic(sf::Music &music);
    bool checkMusicPlaying();
    void pauseOrResumeMusic(sf::Music &music);
    float calculateSongProgressBar(sf::Music &music);
    sf::Time &getCurrentTime();
};

#endif // MUSICLIBRARY_AUDIOPLAYER_HPP