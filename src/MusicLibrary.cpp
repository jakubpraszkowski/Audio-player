#include "../include/Audio-player/MusicLibrary.hpp"

MusicLibrary::MusicLibrary(fs::path directory) {
    directory_ = "/home/${USER}/Music";
}

void MusicLibrary::AddPlaylist(const Playlist &playlist) {
    all_playlists_.push_back(playlist);
}

template <typename T>
void MusicLibrary::PrintVector(const std::vector<T> &vec) const {
    for (const auto &item : vec) {
        std::cout << item << std::endl;
    }
}

template <typename T> bool MusicLibrary::IsEmpty(std::vector<T> &vec) {
    return vec.empty();
}

void MusicLibrary::UpdateSongs(FileManager &file_manager) {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    for (const auto &path : file_manager.get_ogg_file_paths()) {
        TagLib::FileRef file_ref(path.c_str());
        if (!file_ref.isNull() && file_ref.tag()) {
            auto song = create_song_from_tag(file_ref, path);
            all_songs_.push_back(song);
            AddSongToAlbum(song->get_album(), song);
        }
    }
}

std::shared_ptr<Song> MusicLibrary::create_song_from_tag(
    TagLib::FileRef &file_ref, const std::string &path) const {
    TagLib::Tag *tag = file_ref.tag();
    std::string title = tag->title().toCString(true);
    std::string artist = tag->artist().toCString(true);
    std::string album_name = tag->album().toCString(true);
    std::string genre = tag->genre().toCString(true);
    unsigned int year = tag->year();
    int duration = file_ref.audioProperties()->lengthInSeconds();
    return std::make_shared<Song>(
        title, artist, album_name, genre, year, duration, path);
}

void MusicLibrary::AddSongToAlbum(
    const std::string &album_name, const std::shared_ptr<Song> &song) {
    auto &album = all_albums_map_[album_name];
    if (album.get_title().empty()) {
        album = Album(album_name);
        all_albums_.push_back(album);
    }
    album.add_song(song);
}

const std::unordered_map<std::string, Album> &
MusicLibrary::get_albums_map() const {
    return all_albums_map_;
}

std::vector<Album> &MusicLibrary::get_albums() { return all_albums_; }

Song MusicLibrary::get_song(const std::string &song_title) {
    for (auto &song_ptr : all_songs_) {
        if (song_ptr->get_title() == song_title) {
            return *song_ptr;
        }
    }
    throw std::runtime_error("Song not found");
}

MusicLibrary::SongsVector &MusicLibrary::get_songs() { return all_songs_; }

std::vector<Playlist> &MusicLibrary::get_playlists() { return all_playlists_; }