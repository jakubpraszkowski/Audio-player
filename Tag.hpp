#ifndef MUSICLIBRARY_TAG_HPP
#define MUSICLIBRARY_TAG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include "Song.hpp"

class Tag {
protected:
    std::string filePath;
    size_t fileSize;
    std::map<std::string, std::string> tagsMap;
public:
    Tag();
    Tag(std::string filePath);
    Tag(std::string filePath, size_t fileSize);
    static size_t readFileSize(Tag &t1);
    virtual std::map<std::string, std::string> searchForTags(std::map<std::string, std::string> _tagsMap) = 0;
    virtual bool readTag() = 0;
    virtual void proceedTag() = 0;
    virtual void printTag(std::map<std::string, std::string> _tagsMap) = 0;
};


#endif //MUSICLIBRARY_TAG_HPP
