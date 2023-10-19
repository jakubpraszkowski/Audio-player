#include "../include/Audio-player/AudioPlayer.hpp"
#include "../include/Audio-player/FileManager.hpp"
#include "../include/Audio-player/MusicLibrary.hpp"
#include "../include/Audio-player/Tag.hpp"
#include "../include/Audio-player/UserInterface.hpp"
#include <unistd.h>

int main() {
    FileManager fm;
    fm.scanDirectory();
    MusicLibrary ml;
    ml.updateSongs(fm);
    UserInterface ui;
    AudioPlayer ap;
    ui.createWindow(ml, ap);
    return 0;
}