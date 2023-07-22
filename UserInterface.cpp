#include "UserInterface.h"

void UserInterface::printMenu() {
    std::cout << "1. Add song" << std::endl;
    std::cout << "2. Add playlist" << std::endl;
    std::cout << "3. Remove song" << std::endl;
    std::cout << "4. Remove playlist" << std::endl;
    std::cout << "5. Sort songs" << std::endl;
    std::cout << "6. Sort playlists" << std::endl;
    std::cout << "7. Exit" << std::endl;
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

void UserInterface::Menu() {
    welcomeMessage();
    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Add song" << std::endl;
                break;
            case 2:
                std::cout << "Add playlist" << std::endl;
                break;
            case 3:
                std::cout << "Remove song" << std::endl;
                break;
            case 4:
                std::cout << "Remove playlist" << std::endl;
                break;
            case 5:
                std::cout << "Sort songs" << std::endl;
                break;
            case 6:
                std::cout << "Sort playlists" << std::endl;
                break;
            case 7:
                std::cout << "Exit" << std::endl;
                return;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }
}

void UserInterface::welcomeMessage() {
    std::cout << "Welcome to the Music Library!" << std::endl;
}
