#ifndef MUSICLIBRARY_TAG_H
#define MUSICLIBRARY_TAG_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include "Song.h"

class Tag : public Song {
    std::string filePath;
    size_t fileSize;
public:
//    static std::string &getFilePath();
//
//    static void setFilePath(const std::string &path);
//
//    static size_t getFileSize();
//
//    static void setFileSize(size_t fileSize);

    struct VorbisComment {
        std::string title;
        std::string artist;
        std::string album;
        char oggHeader[4];
        unsigned char oggCommLength[4];
        std::map<std::string, std::string> commentHeader;

        void readVorbisComment(Tag &t1);
    };

    Tag(std::string filePath);

    template<typename T, size_t N>
    static void reverseTab(T (&arr)[N]);

    static size_t readFileSize(Tag &t1);
};


#endif //MUSICLIBRARY_TAG_H
