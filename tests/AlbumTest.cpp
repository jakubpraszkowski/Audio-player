#include "../src/Album.cpp"
#include "../src/Song.cpp"
#include <gtest/gtest.h>
#include <memory>

class AlbumTest : public ::testing::Test {
  protected:
    std::shared_ptr<Song> song1 = std::make_shared<Song>("Song1", 200);
    std::shared_ptr<Song> song2 = std::make_shared<Song>("Song2", 200);
    Album album = Album("Test Album");
};

TEST_F(AlbumTest, TestAlbumName) { EXPECT_EQ(album.getTitle(), "Test Album"); }

TEST_F(AlbumTest, TestAddSong) {
    album.addSong(song1);
    EXPECT_EQ(album.getAlbumSongs().size(), 1);
    EXPECT_EQ(album.getAlbumSongs()[0]->getTitle(), "Song1");
}

TEST_F(AlbumTest, TestMultipleAddSong) {
    album.addSong(song1);
    album.addSong(song2);
    EXPECT_EQ(album.getAlbumSongs().size(), 2);
    EXPECT_EQ(album.getAlbumSongs()[0]->getTitle(), "Song1");
    EXPECT_EQ(album.getAlbumSongs()[1]->getTitle(), "Song2");
}