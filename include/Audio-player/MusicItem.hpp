#ifndef MUSICLIBRARY_MUSICITEM_HPP
#define MUSICLIBRARY_MUSICITEM_HPP

#include <string>

#ifdef _WIN32
#include <_bsd_types.h>
#endif

class MusicItem {
protected:
    std::string name;
    std::string creator;
    u_int year;
    u_int size;
    u_int duration;
public:
};


#endif //MUSICLIBRARY_MUSICITEM_HPP
