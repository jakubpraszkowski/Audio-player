#include "../include/Audio-player/MusicLibrary.hpp"

MusicLibrary::MusicLibrary(fs::path directory) {
    directory_ = "/home/${USER}/Music";
}

void MusicLibrary::AddPlaylist(const Playlist &playlist) {
    all_playlists_.push_back(playlist);
}

void MusicLibrary::UpdateSongs(FileManager &file_manager) {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    for (const auto &path : file_manager.get_ogg_file_paths()) {
        TagLib::FileRef file_ref(path.c_str());
        if (!file_ref.isNull() && file_ref.tag()) {
            auto song = CreateSongFromTag(file_ref, path);
            all_songs_.push_back(song);
            AddSongToAlbum(song->get_album(), song);
        }
    }
}

const std::unordered_map<std::string, Album> &
MusicLibrary::get_albums_map() const {
    return all_albums_map_;
}

std::vector<Album> &MusicLibrary::get_albums() { return all_albums_; }

Song MusicLibrary::get_song(const std::string &song_title) const {
    for (const auto &song_ptr : all_songs_) {
        if (song_ptr->get_title() == song_title) {
            return *song_ptr;
        }
    }
    throw std::runtime_error("Song not found");
}

MusicLibrary::SongsVector &MusicLibrary::get_songs() { return all_songs_; }

std::vector<Playlist> &MusicLibrary::get_playlists() { return all_playlists_; }

std::shared_ptr<Song> MusicLibrary::CreateSongFromTag(
    TagLib::FileRef &file_ref, const std::string &path) const {
    TagLib::Tag *tag = file_ref.tag();
    return std::make_shared<Song>(
        tag->title().toCString(true), tag->artist().toCString(true),
        tag->album().toCString(true), tag->genre().toCString(true), tag->year(),
        file_ref.audioProperties()->lengthInSeconds(), path);
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

template <typename T>
void MusicLibrary::PrintVector(const std::vector<T> &vec) const {
    for (const auto &item : vec) {
        std::cout << item << std::endl;
    }
}

template <typename T>
bool MusicLibrary::IsEmpty(const std::vector<T> &vec) const {
    return vec.empty();
}