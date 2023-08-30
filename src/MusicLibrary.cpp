#include <algorithm>
#include "../include/Audio-player/MusicLibrary.hpp"

MusicLibrary::MusicLibrary(fs::path _directory){
    this->directory = "/home/${USER}/Music";
}

void MusicLibrary::addSong(const Song& song) {
    songs->push_back(song);
}

void MusicLibrary::addPlaylist(const Playlist& playlist) {
    playlists->push_back(playlist);
}

//template <typename T>
//void MusicLibrary::removeItem(const std::string &itemTitle) {
//    if (std::is_same<T, Song>::value) {
//        for (auto it = songs.begin(); it != songs.end(); ++it) {
//            if (it->getTitle() == itemTitle) {
//                songs.erase(it);
//                std::cout << "Song '" << itemTitle << "' removed from the library." << std::endl;
//                return;
//            }
//        }
//        std::cout << "Song '" << itemTitle << "' not found in the library." << std::endl;
//    } else if (std::is_same<T, Playlist>::value) {
//        for (auto it = playlists.begin(); it != playlists.end(); ++it) {
//            if (it->getTitle() == itemTitle) {
//                playlists.erase(it);
//                std::cout << "Playlist '" << itemTitle << "' removed from the library." << std::endl;
//                return;
//            }
//        }
//        std::cout << "Playlist '" << itemTitle << "' not found in the library." << std::endl;
//    } else {
//        std::cout << "Error: Invalid type." << std::endl;
//    }
//}

void MusicLibrary::print() {
    for (const auto& item : *songs) {
        std::cout << item << std::endl;
    }
}

std::vector<Playlist> &MusicLibrary::getPlaylists() {
    return *playlists;
}

std::vector<Song> &MusicLibrary::getSongs() {
    return *songs;
}

void MusicLibrary::findOggFiles(const fs::path &_directory) {
    for (fs::recursive_directory_iterator it(_directory), end; it != end; ++it) {
        if (fs::is_regular_file(*it) && it->path().extension() == ".ogg") {
            oggFiles->push_back(it->path().filename().string());
        }
    }
}

template<typename T>
bool MusicLibrary::isEmpty(std::vector<T> &vector) {
    if (vector.empty()) {
        return true;
    }
    return false;
}

template<typename T>
void MusicLibrary::initializeVector(std::vector<T> &vector) {
    vector = new std::vector<T>();
}