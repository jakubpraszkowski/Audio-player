#ifndef MUSICLIBRARY_AUDIOPLAYER_H
#define MUSICLIBRARY_AUDIOPLAYER_H

#include <iostream>
#include <filesystem>
#include "Song.h"

namespace fs = std::filesystem;

class AudioPlayer {
    fs::path path, directory;

public:
    AudioPlayer();
    void searchForAudioFiles(const fs::path& dr);
};


#endif //MUSICLIBRARY_AUDIOPLAYER_H
