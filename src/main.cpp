#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/Tag.hpp"
#include "../include/Audio-player/MusicLibrary.hpp"

int main() {


    fs::path dir = "/home/kubuski/Music";
    std::cout << dir << std::endl;

    MusicLibrary ml;
    ml.findOggFiles(dir);

    return 0;
    // UserInterface ui;

    // ui.mainMenu();
    // return 0;
}
