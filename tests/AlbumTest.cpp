#include "../src/Album.cpp"
#include "../src/Song.cpp"
#include <gtest/gtest.h>
#include <memory>

class AlbumTest : public ::testing::Test, public Song {
  public:
    bool operator==(const Album &rhs) const {
        return get_title() == rhs.get_title();
    }
    bool operator==(const Song &rhs) const {
        return get_title() == rhs.get_title() && get_artist() == rhs.get_artist() &&
               get_album() == rhs.get_album() && get_genre() == rhs.get_genre() &&
               get_year() == rhs.get_year() &&
               get_duration() == rhs.get_duration() && get_path() == rhs.get_path();
    }

  protected:
    std::shared_ptr<Song> expected_song1 = std::make_shared<Song>("Song1", 200);
    std::shared_ptr<Song> expected_song2 = std::make_shared<Song>("Song2", 200);
    std::shared_ptr<Song> expected_song3 = std::make_shared<Song>(
        "Title1", "Creator1", "Album", "Country", 1997, 2000, "~/nice");
    Album album = Album("Test Album");
};

TEST_F(AlbumTest, TestAlbumName) { EXPECT_EQ(album.get_title(), "Test Album"); }

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