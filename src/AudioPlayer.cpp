#include "../include/Audio-player/AudioPlayer.hpp"

void AudioPlayer::loadSound2Queue(int &whichItem, std::vector<Song> &vec) {
    songQueue.push_back(vec[whichItem]);
}

void AudioPlayer::loadSound2Queue(std::vector<Song> &vec) {
    for (auto &song : vec) {
        songQueue.push_back(song);
    }
}

void AudioPlayer::playQueue() {
    while (true) {
        if (songQueue.empty()) {
            music.pause();
        } else {
            music.openFromFile(songQueue.front().getPath());
            music.play();
            currentTime = music.getPlayingOffset();
            sf::sleep(sf::seconds(songQueue.front().getDuration()));
            songQueue.pop_front();
        }
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

void AudioPlayer::pauseOrResumeMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(musicMutex);
    if (music.getStatus() == sf::Music::Playing) {
        music.pause();
    } else {
        music.play();
    }
}

void AudioPlayer::advanceForwardMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(musicMutex);
    sf::Time time = music.getPlayingOffset();
    music.setPlayingOffset(time + sf::seconds(5.f));
}

void AudioPlayer::advanceBackwardMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(musicMutex);
    sf::Time time = music.getPlayingOffset();
    music.setPlayingOffset(time - sf::seconds(5.f));
}

void AudioPlayer::stopMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(musicMutex);
    music.stop();
    songQueue.clear();
}

sf::Time &AudioPlayer::getCurrentTime() { return currentTime; }

float AudioPlayer::calculateSongProgressBar(sf::Music &music) {
    std::unique_lock<std::mutex> lock(musicMutex);
    sf::Time time = music.getPlayingOffset();
    sf::Time duration = music.getDuration();
    return time.asSeconds() / duration.asSeconds();
}