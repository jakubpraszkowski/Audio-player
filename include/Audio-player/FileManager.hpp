#ifndef MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_FILEMANAGER_HPP
#define MUSICLIBRARY_INCLUDE_AUDIO_PLAYER_FILEMANAGER_HPP

#include <filesystem>
#include <vector>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

namespace fs = std::filesystem;

class FileManager {
  public:
    FileManager();

    void scanDirectory();

    void changeScanningDirectory(fs::path &newDirectory);

    void printOggFilePaths();

    std::vector<std::string> &getOggFilePaths();

  private:
    fs::path directory;

    std::vector<std::string> oggFilePaths;
};

#endif