#ifndef MUSICLIBRARY_USERINTERFACE_H
#define MUSICLIBRARY_USERINTERFACE_H

#include <iostream>
#include "MusicLibrary.h"

class UserInterface {
public:
    static void printMenu();
    static void printSortSongMenu();
    static void printSortPlaylistMenu();
    static void welcomeMessage();

    void Menu();

};


#endif //MUSICLIBRARY_USERINTERFACE_H
