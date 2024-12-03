#pragma once

#include <sys/inotify.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

namespace fs = std::filesystem;

const int kEventSize = sizeof(struct inotify_event);
const int kEventBufLen = 1024 * (kEventSize + 16);

class FileManager {
  public:
    FileManager();

    void ScanDirectory();

    void ChangeScanningDirectory(fs::path &new_directory);

    void PrintOggFilePaths();

    std::vector<std::string> &get_ogg_file_paths();

    void SaveFilePaths();

    void LoadFilePaths();

    bool CheckForChanges();

    fs::path &get_directory();

  private:
    fs::path directory_;
    std::vector<std::string> ogg_file_paths_;
};
