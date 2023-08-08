#ifndef MUSICLIBRARY_AUDIOPLAYER_HPP
#define MUSICLIBRARY_AUDIOPLAYER_HPP

#include <iostream>
#include <filesystem>
#include "Song.hpp"

namespace fs = std::filesystem;

class AudioPlayer {
    fs::path path, directory;

public:
    AudioPlayer();
    void searchForAudioFiles(const fs::path& dr);
};


#endif //MUSICLIBRARY_AUDIOPLAYER_HPP
