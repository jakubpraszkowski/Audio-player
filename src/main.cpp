#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/Tag.hpp"
#include "../include/Audio-player/MusicLibrary.hpp"
#include "../include/Audio-player/FileManager.hpp"
#include "../include/Audio-player/AudioPlayer.hpp"
#include <unistd.h>

int main()
{
     setlocale(LC_ALL, "pl_PL.UTF-8");
    FileManager fm;
    fm.scanDirectory();
    MusicLibrary ml;
    ml.updateSongs(fm);
    UserInterface ui;
    ui.createWindow(ml);
    // AudioPlayer ap;

    // ap.loadSound2Buffer(ml.getSong("ALOHA"));
    return 0;
}