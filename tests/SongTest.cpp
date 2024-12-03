#include "../include/Audio-player/Song.hpp"

#include <gtest/gtest.h>

class SongTest : public ::testing::Test {
  protected:
    Song song{"Title", "Artist", "Album", "Genre", 2000, 180, "Path"};
};

TEST_F(SongTest, TestTitle) { EXPECT_EQ(song.get_title(), "Title"); }

TEST_F(SongTest, TestArtist) { EXPECT_EQ(song.get_artist(), "Artist"); }

TEST_F(SongTest, TestAlbum) { EXPECT_EQ(song.get_album(), "Album"); }

TEST_F(SongTest, TestGenre) { EXPECT_EQ(song.get_genre(), "Genre"); }

TEST_F(SongTest, TestYear) { EXPECT_EQ(song.get_year(), 2000); }

TEST_F(SongTest, TestDuration) { EXPECT_EQ(song.get_duration(), 180); }

TEST_F(SongTest, TestPath) { EXPECT_EQ(song.get_path(), "Path"); }