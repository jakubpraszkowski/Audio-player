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
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <filesystem>

class Tag
{
public:
    void getOggTag(std::filesystem::path &file);
};

#endif // MUSICLIBRARY_TAG_HPP
