#include "../include/Audio-player/AudioPlayer.hpp"

#define AUDIO_EXTENSION ".ogg"

AudioPlayer::AudioPlayer() {
    char* envUsername = std::getenv("USERNAME");
    if(envUsername != nullptr) {
        std::string temp = "/home" + std::string(envUsername) + "/Music";
        directory = fs::path(temp);
    }
}

void AudioPlayer::searchForAudioFiles(const fs::path& dr) {
    for (const auto& entry : fs::directory_iterator(dr)) {
        if (entry.path().extension() == AUDIO_EXTENSION) {
            std::cout << entry.path() << std::endl;
        }
    }
}