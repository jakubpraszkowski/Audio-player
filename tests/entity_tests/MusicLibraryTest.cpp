#include "../../include/Audio-player/MusicLibrary.hpp"
#include "../../include/Audio-player/FileManager.hpp"

#include <gtest/gtest.h>

class MusicLibraryTest : public ::testing::Test {
  protected:
    MusicLibrary music_library;
    FileManager file_manager;
};

TEST_F(MusicLibraryTest, TestUpdateSongs) {
    file_manager.ScanDirectory();
    music_library.UpdateSongs(file_manager);
    EXPECT_FALSE(music_library.get_songs().empty());
}

TEST_F(MusicLibraryTest, TestAddPlaylist) {
    Playlist playlist("Test Playlist");
    music_library.AddPlaylist(playlist);
    EXPECT_EQ(music_library.get_playlists().size(), 1);
}

TEST_F(MusicLibraryTest, TestGetSong) {
    file_manager.ScanDirectory();
    music_library.UpdateSongs(file_manager);
    auto song = music_library.get_song("Song1");
    EXPECT_EQ(song.get_title(), "Song1");
}
