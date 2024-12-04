#include "../../include/Audio-player/AudioPlayer.hpp"
#include "../../include/Audio-player/Song.hpp"

#include <gtest/gtest.h>
#include <memory>

class AudioPlayerTest : public ::testing::Test {
  protected:
    AudioPlayer audio_player;
    std::shared_ptr<Song> song1 = std::make_shared<Song>("Song1", 200);
    std::shared_ptr<Song> song2 = std::make_shared<Song>("Song2", 300);
};

TEST_F(AudioPlayerTest, TestLoadSoundToQueue) {
    AudioPlayer::SongsVector songs = {song1, song2};
    audio_player.LoadSoundToQueue(0, songs);
    EXPECT_EQ(audio_player.get_song_queue().size(), 1);
    EXPECT_EQ(audio_player.get_song_queue_front()->get_title(), "Song1");
}

TEST_F(AudioPlayerTest, TestPlayQueue) {
    AudioPlayer::SongsVector songs = {song1, song2};
    audio_player.LoadSoundToQueue(0, songs);
    audio_player.PlayQueue();
    EXPECT_TRUE(audio_player.is_deque_empty());
}

TEST_F(AudioPlayerTest, TestPauseOrResumeMusic) {
    audio_player.PauseOrResumeMusic();
    EXPECT_FALSE(audio_player.check_music_playing());
}

TEST_F(AudioPlayerTest, TestStopMusic) {
    audio_player.StopMusic();
    EXPECT_TRUE(audio_player.is_deque_empty());
}
