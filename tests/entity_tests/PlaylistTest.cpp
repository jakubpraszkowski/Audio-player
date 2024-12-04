#include "../../include/Audio-player/Playlist.hpp"
#include "../../include/Audio-player/Song.hpp"

#include <gtest/gtest.h>
#include <memory>

class PlaylistTest : public ::testing::Test {
  protected:
    std::shared_ptr<Song> song1 = std::make_shared<Song>("Song1", 200);
    std::shared_ptr<Song> song2 = std::make_shared<Song>("Song2", 300);
    Playlist playlist{"Test Playlist"};
};

TEST_F(PlaylistTest, TestAddSongToPlaylist) {
    playlist.AddSongToPlaylist(song1);
    EXPECT_EQ(playlist.get_playlist_songs().size(), 1);
    EXPECT_EQ(playlist.get_playlist_songs()[0]->get_title(), "Song1");
}

TEST_F(PlaylistTest, TestRemoveSongFromPlaylist) {
    playlist.AddSongToPlaylist(song1);
    playlist.RemoveSongFromPlaylist("Song1");
    EXPECT_TRUE(playlist.get_playlist_songs().empty());
}

TEST_F(PlaylistTest, TestCalculateDuration) {
    playlist.AddSongToPlaylist(song1);
    playlist.AddSongToPlaylist(song2);
    EXPECT_EQ(playlist.CalculateDuration(), 500);
}
