#ifndef MUSICLIBRARY_FILEMANAGER_HPP
#define MUSICLIBRARY_FILEMANAGER_HPP

#include <filesystem>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;

class FileManager {
    fs::path directory;
    std::vector<std::string> oggFilePaths;

public:
    FileManager();
    void scanDirectory();
    void changeScanningDirectory(fs::path &newDirectory);
    void printOggFilePaths();
};

#endif