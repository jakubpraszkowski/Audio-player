#include "../include/Audio-player/UserInterface.hpp"
#include "../include/Audio-player/Tag.hpp"
#include "../include/Audio-player/MusicLibrary.hpp"
#include "../include/Audio-player/FileManager.hpp"
#include "../include/Audio-player/AudioPlayer.hpp"

int main()
{
    FileManager fm;
    fm.scanDirectory();
    AudioPlayer ap;
    MusicLibrary ml;
    ml.updateSongs(fm);
    // ml.printSongs();
    ap.loadSound2Buffer(ml.getSong("Fukaj, charlie moncler - ALOHA"));
}
