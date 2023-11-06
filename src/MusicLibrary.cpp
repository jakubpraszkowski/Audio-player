#include "../include/Audio-player/MusicLibrary.hpp"
#include <algorithm>

MusicLibrary::MusicLibrary(fs::path _directory) {
    this->directory = "/home/${USER}/Music";
}

void MusicLibrary::addSong(const Song &song) { allSongs.push_back(song); }

void MusicLibrary::addPlaylist(const Playlist &playlist) {
    allPlaylists.push_back(playlist);
}

template <typename T>
void MusicLibrary::printVector(const std::vector<T> &vec) {
    for (const auto &item : vec) {
        std::cout << item << std::endl;
    }
}

template <typename T> bool MusicLibrary::isEmpty(std::vector<T> &vector) {
    if (vector.empty()) {
        return true;
    }
    return false;
}

void MusicLibrary::updateSongs(FileManager &fm) {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    std::map<std::string, Album> albumMap;
    for (const auto &path : fm.getOggFilePaths()) {
        TagLib::FileRef f(path.c_str());
        if (!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            std::string title = tag->title().toCString();
            std::string artist = tag->artist().toCString();
            std::string album = tag->album().toCString();
            std::string genre = tag->genre().toCString();
            u_int year = tag->year();
            int duration = f.audioProperties()->lengthInSeconds();
            Song song(title, artist, album, genre, year, duration, path);
            allSongs.push_back(song);
            albumMap[album].addSong(song);
        }
    }
}

Song MusicLibrary::getSong(const std::string &songTitle) {
    for (auto &song : allSongs) {
        if (song.getTitle() == songTitle) {
            return song;
        }
    }
    throw std::runtime_error("Song not found");
}