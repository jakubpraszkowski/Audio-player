#include "../include/Audio-player/AudioPlayer.hpp"

void AudioPlayer::LoadSoundToQueue(int which_item, SongsVector &vec) {
    song_queue_.push_back(vec[which_item]);
}

void AudioPlayer::LoadSoundToQueue(int which_item, std::vector<Album> &vec) {
    for (const auto &song : vec[which_item].get_album_songs()) {
        song_queue_.push_back(song);
    }
}

void AudioPlayer::PlayQueue() {
    while (!song_queue_.empty()) {
        auto song = song_queue_.front();
        music_.openFromFile(song->get_path());
        music_.play();
        current_time_ = music_.getPlayingOffset();
        sf::sleep(sf::seconds(song->get_duration()));
        song_queue_.pop_front();
    }
    music_.pause();
}

bool AudioPlayer::is_deque_empty() const { return song_queue_.empty(); }

sf::Music &AudioPlayer::get_current_music() { return music_; }

bool AudioPlayer::check_music_playing() const {
    return music_.getStatus() == sf::Music::Playing;
}

void AudioPlayer::PauseOrResumeMusic() {
    std::unique_lock<std::mutex> lock(music_mutex_);
    if (music_.getStatus() == sf::Music::Playing) {
        music_.pause();
    } else {
        music_.play();
    }
}

void AudioPlayer::AdvanceForwardMusic() {
    std::unique_lock<std::mutex> lock(music_mutex_);
    music_.setPlayingOffset(music_.getPlayingOffset() + sf::seconds(5.f));
}

void AudioPlayer::AdvanceBackwardMusic() {
    std::unique_lock<std::mutex> lock(music_mutex_);
    music_.setPlayingOffset(music_.getPlayingOffset() - sf::seconds(5.f));
}

void AudioPlayer::StopMusic() {
    std::unique_lock<std::mutex> lock(music_mutex_);
    music_.stop();
    song_queue_.clear();
}

void AudioPlayer::ShuffleQueue() {
    std::shuffle(
        song_queue_.begin(), song_queue_.end(),
        std::default_random_engine(
            std::chrono::system_clock::now().time_since_epoch().count()));
}

sf::Time AudioPlayer::get_current_time() const { return current_time_; }

float AudioPlayer::CalculateSongProgressBar() const {
    std::unique_lock<std::mutex> lock(music_mutex_);
    return music_.getPlayingOffset().asSeconds() /
           music_.getDuration().asSeconds();
}

std::deque<std::shared_ptr<Song>> &AudioPlayer::get_song_queue() {
    return song_queue_;
}

std::shared_ptr<Song> &AudioPlayer::get_song_queue_front() {
    return song_queue_.front();
}
