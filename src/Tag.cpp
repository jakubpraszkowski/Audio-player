#include "../include/Audio-player/Tag.hpp"

Tag::Tag(std::string filePath) {
    this->filePath = filePath;
}

size_t Tag::readFileSize(Tag &t1) {
    std::ifstream file(t1.filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Error opening file " << t1.filePath << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    t1.fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    file.close();
    return t1.fileSize;
}
