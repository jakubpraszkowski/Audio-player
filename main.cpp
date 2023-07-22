#include <iostream>
#include "MusicLibrary.h"
#include "UserInterface.h"

int main() {
    MusicLibrary<Song> musicLibrary;
    std::vector<Song> songs;

    Song song1("Bong", "Crtist1", "Album1", "Genre1", 2000, 200);
    Song song2("Song", "Brtist2", "Album2", "Genre2", 2001, 201);
    Song song3("Aong", "Atist3", "Album3", "Genre3", 2002, 202);

    musicLibrary.addSong(song1);
    musicLibrary.addSong(song2);
    musicLibrary.addSong(song3);

    musicLibrary.sortByName();

    musicLibrary.print();

    musicLibrary.sortByCreator();
    musicLibrary.print();



}
