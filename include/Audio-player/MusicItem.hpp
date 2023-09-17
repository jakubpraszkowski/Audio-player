#ifndef MUSICLIBRARY_MUSICITEM_HPP
#define MUSICLIBRARY_MUSICITEM_HPP

#include <string>

class MusicItem {
protected:
    std::string name;
    std::string creator;
    u_int size;
    u_int duration;
public:
    virtual u_int calculateDuration() = 0;
};

#endif //MUSICLIBRARY_MUSICITEM_HPP
