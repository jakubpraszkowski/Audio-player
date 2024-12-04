#include "../../include/Audio-player/Song.hpp"

#include <gtest/gtest.h>

class SongTest : public ::testing::Test {
  protected:
    Song song{"Title", "Artist", "Album", "Genre", 2000, 180, "Path"};
};

TEST(SongDefaultConstructorTest, TestDefaultConstructor) {
    Song default_song;
    EXPECT_EQ(default_song.get_title(), "");
    EXPECT_EQ(default_song.get_artist(), "");
    EXPECT_EQ(default_song.get_album(), "");
    EXPECT_EQ(default_song.get_genre(), "");
    EXPECT_EQ(default_song.get_year(), 0);
    EXPECT_EQ(default_song.get_duration(), 0);
    EXPECT_EQ(default_song.get_path(), "");
}

TEST(SongParameterizedConstructorTest, TestParameterizedConstructor) {
    Song param_song{"Title", "Artist", "Album", "Genre", 2000, 180, "Path"};
    EXPECT_EQ(param_song.get_title(), "Title");
    EXPECT_EQ(param_song.get_artist(), "Artist");
    EXPECT_EQ(param_song.get_album(), "Album");
    EXPECT_EQ(param_song.get_genre(), "Genre");
    EXPECT_EQ(param_song.get_year(), 2000);
    EXPECT_EQ(param_song.get_duration(), 180);
    EXPECT_EQ(param_song.get_path(), "Path");
}

TEST(SongComparisonTest, TestCompareByDuration) {
    Song song1{"Title1", "Artist1", "Album1", "Genre1", 2000, 180, "Path1"};
    Song song2{"Title2", "Artist2", "Album2", "Genre2", 2001, 200, "Path2"};
    EXPECT_TRUE(Song::CompareByDuration(song1, song2));
    EXPECT_FALSE(Song::CompareByDuration(song2, song1));
}

TEST(SongComparisonTest, TestCompareByTitle) {
    Song song1{"A_Title", "Artist1", "Album1", "Genre1", 2000, 180, "Path1"};
    Song song2{"B_Title", "Artist2", "Album2", "Genre2", 2001, 200, "Path2"};
    EXPECT_TRUE(Song::CompareByTitle(song1, song2));
    EXPECT_FALSE(Song::CompareByTitle(song2, song1));
}

TEST(SongComparisonTest, TestCompareByArtist) {
    Song song1{"Title1", "A_Artist", "Album1", "Genre1", 2000, 180, "Path1"};
    Song song2{"Title2", "B_Artist", "Album2", "Genre2", 2001, 200, "Path2"};
    EXPECT_TRUE(Song::CompareByArtist(song1, song2));
    EXPECT_FALSE(Song::CompareByArtist(song2, song1));
}

TEST(SongComparisonTest, TestCompareByAlbum) {
    Song song1{"Title1", "Artist1", "A_Album", "Genre1", 2000, 180, "Path1"};
    Song song2{"Title2", "Artist2", "B_Album", "Genre2", 2001, 200, "Path2"};
    EXPECT_TRUE(Song::CompareByAlbum(song1, song2));
    EXPECT_FALSE(Song::CompareByAlbum(song2, song1));
}

TEST(SongComparisonTest, TestCompareByGenre) {
    Song song1{"Title1", "Artist1", "Album1", "A_Genre", 2000, 180, "Path1"};
    Song song2{"Title2", "Artist2", "Album2", "B_Genre", 2001, 200, "Path2"};
    EXPECT_TRUE(Song::CompareByGenre(song1, song2));
    EXPECT_FALSE(Song::CompareByGenre(song2, song1));
}

TEST(SongComparisonTest, TestCompareByYear) {
    Song song1{"Title1", "Artist1", "Album1", "Genre1", 1999, 180, "Path1"};
    Song song2{"Title2", "Artist2", "Album2", "Genre2", 2000, 200, "Path2"};
    EXPECT_TRUE(Song::CompareByYear(song1, song2));
    EXPECT_FALSE(Song::CompareByYear(song2, song1));
}

TEST(SongEdgeCaseTest, TestEmptyStrings) {
    Song empty_song{"", "", "", "", 0, 0, ""};
    EXPECT_EQ(empty_song.get_title(), "");
    EXPECT_EQ(empty_song.get_artist(), "");
    EXPECT_EQ(empty_song.get_album(), "");
    EXPECT_EQ(empty_song.get_genre(), "");
    EXPECT_EQ(empty_song.get_year(), 0);
    EXPECT_EQ(empty_song.get_duration(), 0);
    EXPECT_EQ(empty_song.get_path(), "");
}

TEST(SongEdgeCaseTest, TestNegativeValues) {
    Song negative_song{"Title", "Artist", "Album", "Genre", 0, -180, "Path"};
    EXPECT_EQ(negative_song.get_duration(), -180);
}
