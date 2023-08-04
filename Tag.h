#ifndef MUSICLIBRARY_TAG_H
#define MUSICLIBRARY_TAG_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Song.h"

class Tag : public Song {
    std::string filePath;
    size_t fileSize;

public:
    struct VorbisComment {
        std::string title;
        std::string artist;
        std::string album;
        char oggHeader[4];
    };

    Tag(std::string filePath);

    std::unique_ptr<VorbisComment> readVorbisComment();
    //static size_t getFileSize();

    size_t getFileSize() const;

    std::string getFilePath() const;

    static size_t readFileSize();
};


#endif //MUSICLIBRARY_TAG_H
