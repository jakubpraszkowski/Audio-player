#ifndef MUSICLIBRARY_TAG_HPP
#define MUSICLIBRARY_TAG_HPP

#include "Song.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <vector>

class Tag {
  public:
    void getOggTag(std::filesystem::path &file);
};

#endif // MUSICLIBRARY_TAG_HPP
