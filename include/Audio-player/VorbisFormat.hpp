#ifndef MUSICLIBRARY_VORBISFORMAT_HPP
#define MUSICLIBRARY_VORBISFORMAT_HPP

#include "Tag.hpp"
#include "Song.hpp"

class VorbisFormat : public Tag, Song{
    char commHeader[4];
public:
    VorbisFormat() = default;
    size_t userCommentHeaderSize();
    bool readTag() override;
    std::map<std::string, std::string> searchForTags(std::map<std::string, std::string> _tagsMap) override;
    void proceedTag() override;
    void printTag(std::map<std::string, std::string> _tagsMap) override;

};


#endif //MUSICLIBRARY_VORBISFORMAT_HPP
