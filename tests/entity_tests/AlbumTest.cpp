#include "../../include/Audio-player/Album.hpp"
#include "../../include/Audio-player/Song.hpp"

#include <gtest/gtest.h>
#include <memory>

class AlbumTest : public ::testing::Test {
  protected:
    std::shared_ptr<Song> expected_song1 = std::make_shared<Song>("Song1", 200);
    std::shared_ptr<Song> expected_song2 = std::make_shared<Song>("Song2", 200);
    std::shared_ptr<Song> expected_song3 = std::make_shared<Song>(
        "Title1", "Creator1", "Album", "Country", 1997, 2000, "~/nice");
    Album album = Album("Test Album");
};

TEST_F(AlbumTest, TestAlbumName) { EXPECT_EQ(album.get_album(), "Test Album"); }

TEST_F(AlbumTest, TestAddSong) {
    album.add_song(expected_song1);
    EXPECT_EQ(album.get_album_songs().size(), 1);
    EXPECT_EQ(album.get_album_songs()[0]->get_title(), "Song1");
}

TEST_F(AlbumTest, TestMultipleAddSong) {
    album.add_song(expected_song1);
    album.add_song(expected_song2);
    EXPECT_EQ(album.get_album_songs().size(), 2);
    EXPECT_EQ(album.get_album_songs()[0]->get_title(), "Song1");
    EXPECT_EQ(album.get_album_songs()[1]->get_title(), "Song2");
}

TEST_F(AlbumTest, TestDifferentConstuctors) {
    album.add_song(expected_song1);
    album.add_song(expected_song3);
    EXPECT_EQ(album.get_album_songs().size(), 2);
    EXPECT_EQ(album.get_album_songs()[1], expected_song3);
}

TEST_F(AlbumTest, TestEmptyAlbum) {
    EXPECT_EQ(album.get_album_songs().size(), 0);
}
