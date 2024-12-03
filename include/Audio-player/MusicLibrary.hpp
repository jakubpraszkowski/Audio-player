#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Album.hpp"
#include "FileManager.hpp"
#include "Playlist.hpp"
#include "Song.hpp"

namespace fs = std::filesystem;

class MusicLibrary {
  public:
    using SongsVector = std::vector<std::shared_ptr<Song>>;

    MusicLibrary() = default;

    explicit MusicLibrary(const fs::path directory);

    void AddPlaylist(const Playlist &playlist);

    template <typename T> void PrintVector(const std::vector<T> &vec) const;

    template <typename T> bool IsEmpty(const std::vector<T> &vector) const;

    void UpdateSongs(FileManager &file_manager);

    std::shared_ptr<Song> create_song_from_tag(
        TagLib::FileRef &file_ref, const std::string &path) const;

    void AddSongToAlbum(
        const std::string &album_name, const std::shared_ptr<Song> &song);

    void UpdateAlbums();

    const std::unordered_map<std::string, Album> &get_albums_map() const;

    std::vector<Album> &get_albums();

    Song get_song(const std::string &song_title) const;

    SongsVector &get_songs();

    std::vector<Playlist> &get_playlists();

    template <typename T>
    void SortBy(std::vector<T> &vector, bool (*compare)(const T &, const T &)) {
        std::sort(vector.begin(), vector.end(), compare);
    }

  private:
    std::vector<Playlist> all_playlists_;
    SongsVector all_songs_;
    std::unordered_map<std::string, Album> all_albums_map_;
    std::vector<Album> all_albums_;
    fs::path directory_;
};
