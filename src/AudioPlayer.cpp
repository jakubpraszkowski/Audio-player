#include "../include/Audio-player/AudioPlayer.hpp"

void AudioPlayer::loadSound2Buffer(const Song &song)
{
    if (!music.openFromFile(song.getTitle()))
    {
        std::cerr << "Error: Loading file to stream";
        EXIT_FAILURE;
    }
}
