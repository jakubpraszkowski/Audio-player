#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class AudioPlayer {
    fs::path path, directory;

public:
    AudioPlayer();
    void searchForAudioFiles(const fs::path& dr);
};


#endif //MUSICLIBRARY_AUDIOPLAYER_HPP
