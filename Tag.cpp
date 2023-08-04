#include "Tag.h"

Tag::Tag(std::string filePath) {
    this->filePath = std::move(filePath);
}

std::unique_ptr<Tag::VorbisComment> Tag::readVorbisComment() {
    std::unique_ptr<VorbisComment> comment = std::make_unique<VorbisComment>();

    fileSize = readFileSize();

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    //file.seekg(-4, std::ios::end);
}

size_t Tag::readFileSize() {
    std::unique_ptr<VorbisComment> tempComm = std::make_unique<VorbisComment>();
    std::string filePath;
    size_t fileSize;

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Error opening file" << filePath << std::endl;
        return 1;
    }

    tempComm->oggHeader;
    file.read(tempComm->oggHeader, 4);

    if (std::string(tempComm->oggHeader, 4) != "OggS") {
        std::cerr << "Error: File is not an OGG file" << std::endl;
        return 2;
    }

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.close();

    return fileSize;
}

std::string Tag::getFilePath() const {
    return filePath;
}
