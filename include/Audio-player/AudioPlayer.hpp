#pragma once

#include <deque>
#include <memory>
#include <mutex>
#include <random>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include "Album.hpp"
#include "Playlist.hpp"
#include "Song.hpp"

class AudioPlayer {
  public:
    using SongsVector = std::vector<std::shared_ptr<Song>>;

    AudioPlayer() = default;

    void LoadSoundToQueue(int which_item, SongsVector &vec);
    void LoadSoundToQueue(int which_item, std::vector<Album> &vec);
    void PlayQueue();
    bool is_deque_empty() const;
    sf::Music &get_current_music();
    bool check_music_playing() const;
    void PauseOrResumeMusic();
    void AdvanceForwardMusic();
    void AdvanceBackwardMusic();
    void StopMusic();
    void ShuffleQueue();
    sf::Time get_current_time() const;
    float CalculateSongProgressBar() const;
    std::deque<std::shared_ptr<Song>> &get_song_queue();
    std::shared_ptr<Song> &get_song_queue_front();

  private:
    sf::Music music_;
    std::deque<std::shared_ptr<Song>> song_queue_;
    mutable std::mutex music_mutex_;
    sf::Time current_time_;
};
