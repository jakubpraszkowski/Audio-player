#ifndef MUSICLIBRARY_USERINTERFACE_H
#define MUSICLIBRARY_USERINTERFACE_H

#include <iostream>
#include "MusicLibrary.h"
#include "Song.h"

class UserInterface {
public:
    static void printMenu();
    static void printSortSongMenu();
    static void printSortPlaylistMenu();
    static void welcomeMessage();
    static void clearScreen();
    void sortPlaylistMenu();
    void sortSongMenu(MusicLibrary &ml);

    std::string whichSong2Remove();
    std::string whichPlaylist2Remove();

    void mainMenu();


};


#endif //MUSICLIBRARY_USERINTERFACE_H
