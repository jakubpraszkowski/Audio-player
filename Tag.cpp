#include "Tag.h"

#define OGG_COMMENT_BLOCK_SIZE_START 0x00000064

Tag::Tag(std::string filePath) {
    this->filePath = filePath;
}

void Tag::VorbisComment::readVorbisComment(Tag &t1) {
    std::cout << "przed:" << t1.fileSize << std::endl;

    t1.fileSize = readFileSize(t1);
    std::cout << t1.fileSize;

    std::ifstream file(t1.filePath, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Error: Error opening file " << t1.filePath << std::endl;
        return;
    }

    file.seekg(OGG_COMMENT_BLOCK_SIZE_START, std::ios::beg);
    file.read((char *) (oggCommLength), 4);
    reverseTab(oggCommLength);

    size_t commentLength = (unsigned) (oggCommLength[0] << 24 |
                                       oggCommLength[1] << 16 |
                                       oggCommLength[2] << 8 |
                                       oggCommLength[3]);

    std::vector<char> commentBlock(commentLength);
    file.read(commentBlock.data(), commentLength);

    std::string commentBlockString(commentBlock.data(), commentLength);

    size_t startPos = 0;
    while (startPos < commentBlockString.size()) {
        size_t endPos = commentBlockString.find('=', startPos);
        if (endPos == std::string::npos) {
            break;
        }

        std::string tag = commentBlockString.substr(startPos, endPos - startPos);
        startPos = endPos + 1;
        endPos = commentBlockString.find('\x00', startPos);

        if (endPos == std::string::npos) {
            endPos = commentBlockString.size();
        }

        std::string value = commentBlockString.substr(startPos, endPos - startPos);
        commentHeader[tag] = value;
        startPos = endPos + 1;
    }

    file.close();
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

    char oggHeader[4];
    if (!file.read(oggHeader, 4)) {
        std::cerr << "Error: Failed to read 4 bytes from the file" << std::endl;
        return 3;
    }

    if (std::string(oggHeader, 4) != "OggS") {
        std::cerr << "Error: File is not an OGG file" << std::endl;
        return 2;
    }

    file.close();
    return t1.fileSize;
}

//void Tag::setFilePath(const std::string &path) {
//    Tag::filePath = path;
//}
//
//std::string & Tag::getFilePath() {
//    return Tag::filePath;
//}
//
//void Tag::setFileSize(size_t size) {
//    Tag::fileSize = size;
//}
//
//size_t Tag::getFileSize() {
//    return Tag::fileSize;
//}


template<typename T, size_t N>
void Tag::reverseTab(T (&arr)[N]) {
    std::reverse(arr, arr + N);
}
