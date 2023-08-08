#ifndef MUSICLIBRARY_USERINTERFACE_HPP
#define MUSICLIBRARY_USERINTERFACE_HPP

#include <iostream>
#include "MusicLibrary.hpp"
#include "Song.hpp"

class UserInterface {
public:
    static void printMenu();
    static void printSortSongMenu();
    static void printSortPlaylistMenu();
    static void welcomeMessage();
    static void clearScreen();
    static void sortPlaylistMenu(MusicLibrary &ml);
    static void sortSongMenu(MusicLibrary &ml);

    std::string whichSong2Remove();
    std::string whichPlaylist2Remove();

    void mainMenu();
};

#endif //MUSICLIBRARY_USERINTERFACE_HPP
