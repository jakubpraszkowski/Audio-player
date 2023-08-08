#include "VorbisFormat.hpp"

bool VorbisFormat::readTag() {
    return true;
}

size_t VorbisFormat::userCommentHeaderSize() {
    return 0;
}

std::map<std::string, std::string> VorbisFormat::searchForTags(std::map<std::string, std::string> _tagsMap) {
    return {};
}

void VorbisFormat::proceedTag() {

}

void VorbisFormat::printTag(std::map<std::string, std::string> _tagsMap) {

}
