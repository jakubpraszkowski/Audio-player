#include "../include/Audio-player/FileManager.hpp"

FileManager::FileManager() { directory_ = "/home/kubuski/Music"; }

void FileManager::ScanDirectory() {
    for (fs::recursive_directory_iterator it(directory_), end; it != end;
         it++) {
        if (fs::is_regular_file(*it) && it->path().extension() == ".ogg") {
            ogg_file_paths_.push_back(it->path().string());
        }
    }
}

void FileManager::ChangeScanningDirectory(const fs::path &new_directory) {
    directory_ = new_directory;
}

void FileManager::PrintOggFilePaths() const {
    int count = 0;
    for (const auto &path : ogg_file_paths_) {
        std::cout << path << std::endl;
        count++;
    }
    std::cout << "Total: " << count;
}

std::vector<std::string> &FileManager::get_ogg_file_paths() {
    return ogg_file_paths_;
}

void FileManager::SaveFilePaths() const {
    std::ofstream file("filepaths.txt");
    for (const auto &path : ogg_file_paths_) {
        file << path << std::endl;
    }
    file.close();
}

void FileManager::LoadFilePaths() {
    std::ifstream file("filepaths.txt");
    std::string line;
    while (std::getline(file, line)) {
        ogg_file_paths_.push_back(line);
    }
    file.close();
}

bool FileManager::CheckForChanges() const { return false; }

const fs::path &FileManager::get_directory() const { return directory_; }