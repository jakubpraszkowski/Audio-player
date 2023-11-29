#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include "Album.hpp"
#include "MusicLibrary.hpp"
#include "Playlist.hpp"
#include "Song.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <atomic>
#include <chrono>
#include <deque>
#include <iostream>
#include <random>

class AudioPlayer {
    sf::Music music;
    std::deque<std::shared_ptr<Song>> songQueue;
    std::mutex musicMutex;
    sf::Time currentTime;

  public:
    AudioPlayer() = default;

    void
    loadSound2Queue(int &whichItem, std::vector<std::shared_ptr<Song>> &vec);

    void loadSound2Queue(int &whichItem, std::vector<Album> &vec);

    void playQueue();

    bool isDequeEmpty();

    sf::Music &getCurrentMusic();

    bool checkMusicPlaying();

    void pauseOrResumeMusic(sf::Music &music);

    void advanceForwardMusic(sf::Music &music);

    void advanceBackwardMusic(sf::Music &music);

    void stopMusic(sf::Music &music);

    void shuffleQueue();

    sf::Time &getCurrentTime();

    float calculateSongProgressBar(sf::Music &music);

    std::deque<std::shared_ptr<Song>> &getSongQueue() { return songQueue; }

    std::shared_ptr<Song> &getSongQueueFront() { return songQueue.front(); }
};

#endif // MUSICLIBRARY_AUDIOPLAYER_HPP