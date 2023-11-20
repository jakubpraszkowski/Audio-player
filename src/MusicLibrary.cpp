#include "../include/Audio-player/MusicLibrary.hpp"

MusicLibrary::MusicLibrary(fs::path _directory) {
    this->directory = "/home/${USER}/Music";
}

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
    for (const auto &path : fm.getOggFilePaths()) {
        TagLib::FileRef f(path.c_str());
        if (!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            std::string title = tag->title().toCString();
            std::string artist = tag->artist().toCString();
            std::string albumName = tag->album().toCString();
            std::string genre = tag->genre().toCString();
            u_int year = tag->year();
            int duration = f.audioProperties()->lengthInSeconds();
            std::shared_ptr<Song> song = std::make_shared<Song>(
                title, artist, albumName, genre, year, duration, path);
            allSongs.push_back(song);
            addSongToAlbum(albumName, song);
        }
    }
}

void MusicLibrary::addSongToAlbum(
    const std::string &albumName, const std::shared_ptr<Song> &song) {
    if (albumsMap.find(albumName) == albumsMap.end()) {
        std::shared_ptr<Album> newAlbum = std::make_shared<Album>(albumName);
        newAlbum->addSong(song);
        albumsMap[albumName] = newAlbum;
    } else {
        albumsMap[albumName]->addSong(song);
    }
}

// void MusicLibrary::updateAlbums() {
//     for (auto &songPtr : allSongs) {
//         albums[songPtr->getAlbum()].push_back(*songPtr);
//     }
// }

Song MusicLibrary::getSong(const std::string &songTitle) {
    for (auto &songPtr : allSongs) {
        if (songPtr->getTitle() == songTitle) {
            return *songPtr;
        }
    }
    throw std::runtime_error("Song not found");
}