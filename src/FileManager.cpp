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
    for (const auto &path : ogg_file_paths_) {
        std::cout << path << std::endl;
    }
    std::cout << "Total: " << ogg_file_paths_.size() << std::endl;
}

std::vector<std::string> &FileManager::get_ogg_file_paths() {
    return ogg_file_paths_;
}

void FileManager::SaveFilePaths() const {
    std::ofstream file("filepaths.txt");
    for (const auto &path : ogg_file_paths_) {
        file << path << std::endl;
    }
}

void FileManager::LoadFilePaths() {
    ogg_file_paths_.clear();
    std::ifstream file("filepaths.txt");
    std::string line;
    while (std::getline(file, line)) {
        ogg_file_paths_.push_back(line);
    }
}

const fs::path &FileManager::get_directory() const { return directory_; }

bool FileManager::CheckForChanges() const { return false; }
