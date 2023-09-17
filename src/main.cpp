#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/Tag.hpp"
#include "../include/Audio-player/MusicLibrary.hpp"
#include "../include/Audio-player/FileManager.hpp"

int main() {

    FileManager fm;
    fm.scanFolder();
    fm.printOggFilePaths();
}
