#include "../include/Audio-player/AudioPlayer.hpp"

void AudioPlayer::LoadSoundToQueue(int &which_item, SongsVector &vec) {
    song_queue_.push_back(vec[which_item]);
}

void AudioPlayer::LoadSoundToQueue(int &which_item, std::vector<Album> &vec) {
    for (auto &song : vec[which_item].get_album_songs()) {
        song_queue_.push_back(song);
    }
}

void AudioPlayer::PlayQueue() {
    while (true) {
        if (song_queue_.empty()) {
            music_.pause();
        }

        std::shared_ptr<Song> song = song_queue_.front();
        Song &song_ref = *song;

        music_.openFromFile(song_ref.get_path());
        music_.play();
        current_time_ = music_.getPlayingOffset();
        sf::sleep(sf::seconds(song_ref.get_duration()));
        song_queue_.pop_front();
    }
}

bool AudioPlayer::is_deque_empty() { return song_queue_.empty(); }

sf::Music &AudioPlayer::get_current_music() { return music_; }

bool AudioPlayer::check_music_playing() {
    return music_.getStatus() == sf::Music::Playing;
}

void AudioPlayer::PauseOrResumeMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(music_mutex_);
    if (music.getStatus() == sf::Music::Playing) {
        music.pause();
    }
    music.play();
}

void AudioPlayer::AdvanceForwardMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(music_mutex_);
    sf::Time time = music.getPlayingOffset();
    music.setPlayingOffset(time + sf::seconds(5.f));
}

void AudioPlayer::AdvanceBackwardMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(music_mutex_);
    sf::Time time = music.getPlayingOffset();
    music.setPlayingOffset(time - sf::seconds(5.f));
}

void AudioPlayer::StopMusic(sf::Music &music) {
    std::unique_lock<std::mutex> lock(music_mutex_);
    music.stop();
    song_queue_.clear();
    lock.unlock();
}

void AudioPlayer::ShuffleQueue() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(song_queue_.begin(), song_queue_.end(), rng);
}

sf::Time &AudioPlayer::get_current_time() { return current_time_; }

float AudioPlayer::CalculateSongProgressBar(sf::Music &music) {
    std::unique_lock<std::mutex> lock(music_mutex_);
    sf::Time time = music.getPlayingOffset();
    sf::Time duration = music.getDuration();
    return time.asSeconds() / duration.asSeconds();
}

std::deque<std::shared_ptr<Song>> &AudioPlayer::get_song_queue() {
    return song_queue_;
}

std::shared_ptr<Song> &AudioPlayer::get_song_queue_front() {
    return song_queue_.front();
}