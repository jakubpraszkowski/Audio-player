#include "../include/Audio-player/UserInterface.hpp"

void UserInterface::printMenu() {
    std::cout << "1. Add song" << std::endl;
    std::cout << "2. Add playlist" << std::endl;
    std::cout << "3. Remove song" << std::endl;
    std::cout << "4. Remove playlist" << std::endl;
    std::cout << "5. Sort songs" << std::endl;
    std::cout << "6. Sort playlists" << std::endl;
    std::cout << "7. Show songs" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

void UserInterface::printSortSongMenu() {
    std::cout << "1. Sort by name" << std::endl;
    std::cout << "2. Sort by artist" << std::endl;
    std::cout << "3. Sort by genre" << std::endl;
    std::cout << "4. Sort by duration" << std::endl;
    std::cout << "5. Back" << std::endl;
}

void UserInterface::printSortPlaylistMenu() {
    std::cout << "1. Sort by name" << std::endl;
    std::cout << "2. Sort by duration" << std::endl;
    std::cout << "3. Back" << std::endl;
}

void UserInterface::mainMenu() {
    welcomeMessage();

    Song s1;
    Playlist p1;
    MusicLibrary ml;

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                clearScreen();
                std::cout << "Add song" << std::endl;
                s1.createSong();
                ml.addSong(s1);
                break;
            case 2:
                clearScreen();
                std::cout << "Add playlist" << std::endl;
                p1.createPlaylist();
                ml.addPlaylist(p1);
                break;
            case 3:
                clearScreen();
                std::cout << "Remove song" << std::endl;
                //ml.removeItem<Song>(whichSong2Remove());
                break;
            case 4:
                clearScreen();
                std::cout << "Remove playlist" << std::endl;
                //ml.removeItem<Playlist>(whichPlaylist2Remove());
                break;
            case 5:
                clearScreen();
                std::cout << "Sort songs" << std::endl;
                sortSongMenu(ml);
                break;
            case 6:
                clearScreen();
                std::cout << "Sort playlists" << std::endl;
                sortPlaylistMenu(ml);
                break;
            case 7:
                clearScreen();
                std::cout << "Show songs" << std::endl;
                ml.print();
                break;
            case 8:
                clearScreen();
                std::cout << "Show playlists" << std::endl;
                break;
            case 9:
                clearScreen();
                std::cout << "Exit" << std::endl;
                return;
            default:
                clearScreen();
                std::cout << "Invalid choice" << std::endl;
                printMenu();
                break;
        }
    }
}

void UserInterface::welcomeMessage() {
    std::cout << "Welcome to the Music Library!" << std::endl;
}

void UserInterface::clearScreen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}

std::string UserInterface::whichSong2Remove() {
    std::string songToRemove;
    std::cout << "Enter the title of the song you want to remove: ";
    std::cin >> songToRemove;
    return songToRemove;
}

std::string UserInterface::whichPlaylist2Remove() {
    std::string playlistToRemove;
    std::cout << "Enter the title of the playlist you want to remove: ";
    std::cin >> playlistToRemove;
    return playlistToRemove;
}

void UserInterface::sortSongMenu(MusicLibrary &ml) {
    while(true){
        printSortSongMenu();
        int ch;
        std::cin >> ch;
        switch (ch) {
            case 1:
                clearScreen();
                std::cout << "Sort by name" << std::endl;
                ml.sortBy(ml.getSongs(), Song::compareByTitle);
                break;
            case 2:
                clearScreen();
                std::cout << "Sort by artist" << std::endl;
                ml.sortBy(ml.getSongs(), Song::compareByArtist);
                break;
            case 3:
                clearScreen();
                std::cout << "Sort by genre" << std::endl;
                ml.sortBy(ml.getSongs(), Song::compareByGenre);
                break;
            case 4:
                clearScreen();
                std::cout << "Sort by duration" << std::endl;
                ml.sortBy(ml.getSongs(), Song::compareByDuration);
                break;
            case 5:
                clearScreen();
                std::cout << "Back" << std::endl;
                return;
            default:
                clearScreen();
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }
}

void UserInterface::sortPlaylistMenu(MusicLibrary &ml) {
    while(true){
        printSortPlaylistMenu();
        int ch;
        std::cin >> ch;
        switch (ch) {
            case 1:
                clearScreen();
                std::cout << "Sort by name" << std::endl;
                ml.sortBy(ml.getPlaylists(), Playlist::compareByTitle);
                break;
            case 2:
                clearScreen();
                std::cout << "Sort by duration" << std::endl;
                ml.sortBy(ml.getPlaylists(), Playlist::compareByDuration);
                break;
            case 3:
                clearScreen();
                std::cout << "Sort by creator" << std::endl;
                ml.sortBy(ml.getPlaylists(), Playlist::compareByCreator);
                break;
            case 4:
                clearScreen();
                std::cout << "Sort by year" << std::endl;
                ml.sortBy(ml.getPlaylists(), Playlist::compareByYear);
                break;
            case 5:
                clearScreen();
                std::cout << "Back" << std::endl;
                return;
            default:
                clearScreen();
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }

}

void UserInterface::changeDir(fs::path *nDirectory) {
    std::cout << "Where to look for songs? Please provide the full path: ";
    std::cin >> *nDirectory;
}
