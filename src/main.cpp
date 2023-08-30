#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/Tag.hpp"
#include "../include/Audio-player/MusicLibrary.hpp"

int main() {

    std::vector<std::string> ogg;
    fs::path dir = "/home/kubuski/Music";
    std::cout << dir << std::endl;

    MusicLibrary ml;
    ml.findOggFiles(dir, ogg);
    
    for (auto &file : ogg) {
        std::cout << file << std::endl;
    }

    return 0;
    // UserInterface ui;

    // ui.mainMenu();
    // return 0;
}
