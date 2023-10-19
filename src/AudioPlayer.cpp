#include "../include/Audio-player/AudioPlayer.hpp"

// template <typename T>
void AudioPlayer::loadSound2Queue(int &whichItem, std::vector<Song> &vec) {
    songQueue.push_back(vec[whichItem]);
}

void AudioPlayer::playQueue() {
    if (!songQueue.empty()) {
        music.openFromFile(songQueue.front().getPath());
        music.play();
        sf::sleep(sf::seconds(songQueue.front().getDuration()));
        songQueue.pop_front();
    }
}