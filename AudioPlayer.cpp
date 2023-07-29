#include "AudioPlayer.h"

void AudioPlayer::processAudioFile(const fs::path &path) {

}

void AudioPlayer::searchForAudioFiles(const fs::path &dr) {
    for (const auto& entry : fs::directory_iterator(dr)) {
        if (entry.is_regular_file()) {
            std::string extension = entry.path().extension().string();
            if (extension == ".mp3" || extension == ".wav" || extension == ".flac" || extension == ".ogg") {
                processAudioFile(entry.path());
            }
        } else if (entry.is_directory()) {
            searchForAudioFiles(entry.path());
        }
    }
}

AudioPlayer::AudioPlayer() {
    char* envUsername = std::getenv("USERNAME");
    if(envUsername != nullptr) {
        std::string temp = "/home" + std::string(envUsername) + "/Music";
        directory = fs::path(temp);
    }
}