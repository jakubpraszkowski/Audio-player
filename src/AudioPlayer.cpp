#include "../include/Audio-player/AudioPlayer.hpp"

// template <typename T>
void AudioPlayer::loadSound2Queue(int &whichItem, std::vector<Song> &vec) {
    songQueue.push_back(vec[whichItem]);
}

void AudioPlayer::playQueue() {
    while (!songQueue.empty()) {
        music.openFromFile(songQueue.front().getPath());
        music.play();
        sf::sleep(sf::seconds(songQueue.front().getDuration()));
        songQueue.pop_front();
    }
}

bool AudioPlayer::isDequeEmpty() {
    if (songQueue.empty()) {
        return true;
    } else {
        return false;
    }
}

sf::Music &AudioPlayer::getCurrentMusic() { return music; }

bool AudioPlayer::checkMusicPlaying() {
    if (music.getStatus() == sf::Music::Playing) {
        return true;
    } else {
        return false;
    }
}