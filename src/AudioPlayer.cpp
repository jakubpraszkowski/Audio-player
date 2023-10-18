#include "../include/Audio-player/AudioPlayer.hpp"

template <typename T>
void AudioPlayer::loadSound2Queue(const T sound, const std::vector<T> &vec) {
    for (auto &i : vec) {
        if (!sound.openFromFile(i.getPath())) {
            std::cerr << "Error: Loading file to stream";
            EXIT_FAILURE;
        }
        songQueue.push(i);
    }
}

// void AudioPlayer::loadSound2Buffer(const Song &song) {
//     if (!music.openFromFile(song.getPath())) {
//         std::cerr << "Error: Loading file to stream";
//         EXIT_FAILURE;
//     }
//     music.play();
//     sf::sleep(sf::seconds(song.getDuration()));
// }

// template <typename T> void AudioPlayer::loadVector2Buffer() {}