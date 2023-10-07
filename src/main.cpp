#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/Tag.hpp"
#include "../include/Audio-player/MusicLibrary.hpp"
#include "../include/Audio-player/FileManager.hpp"
#include "../include/Audio-player/AudioPlayer.hpp"
#include <unistd.h>

int main()
{

    UserInterface ui;
    ui.createWindow();
    // FileManager fm;
    // fm.scanDirectory();
    // AudioPlayer ap;
    // MusicLibrary ml;
    // ml.updateSongs(fm);
    // ap.loadSound2Buffer(ml.getSong("ALOHA"));
    return 0;
}