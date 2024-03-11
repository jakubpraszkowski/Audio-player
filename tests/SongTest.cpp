#include "../src/Song.cpp"

#include <gtest/gtest.h>

class SongTest : public ::testing::Test {
  protected:
    Song song{"Title", "Artist", "Album", "Genre", 2000, 180, "Path"};
};

TEST_F(SongTest, TestTitle) { EXPECT_EQ(song.getTitle(), "Title"); }

TEST_F(SongTest, TestArtist) { EXPECT_EQ(song.getArtist(), "Artist"); }

TEST_F(SongTest, TestAlbum) { EXPECT_EQ(song.getAlbum(), "Album"); }

TEST_F(SongTest, TestGenre) { EXPECT_EQ(song.getGenre(), "Genre"); }

TEST_F(SongTest, TestYear) { EXPECT_EQ(song.getYear(), 2000); }

TEST_F(SongTest, TestDuration) { EXPECT_EQ(song.getDuration(), 180); }

TEST_F(SongTest, TestPath) { EXPECT_EQ(song.getPath(), "Path"); }