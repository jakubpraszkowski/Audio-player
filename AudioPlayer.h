#ifndef MUSICLIBRARY_AUDIOPLAYER_H
#define MUSICLIBRARY_AUDIOPLAYER_H

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class AudioPlayer {
    fs::path path, directory;

public:
    AudioPlayer();
    void processAudioFile(const fs::path& path);
    void searchForAudioFiles(const fs::path& dr);
};


#endif //MUSICLIBRARY_AUDIOPLAYER_H
