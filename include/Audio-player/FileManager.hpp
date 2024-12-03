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

constexpr int kEventSize = sizeof(struct inotify_event);
constexpr int kEventBufLen = 1024 * (kEventSize + 16);

class FileManager {
  public:
    FileManager();

    void ScanDirectory();

    void ChangeScanningDirectory(const fs::path &new_directory);

    void PrintOggFilePaths() const;

    std::vector<std::string> &get_ogg_file_paths();

    void SaveFilePaths() const;

    void LoadFilePaths();

    bool CheckForChanges() const;

    const fs::path &get_directory() const;

  private:
    fs::path directory_;
    std::vector<std::string> ogg_file_paths_;
};
