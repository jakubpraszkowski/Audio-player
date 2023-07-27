#include <algorithm>
#include "MusicLibrary.h"

void MusicLibrary::addSong(const Song& song) {
    songs.push_back(song);
}

void MusicLibrary::addPlaylist(const Playlist& playlist) {
    playlists.push_back(playlist);
}

template <typename T>
void MusicLibrary::removeItem(const std::string &itemTitle) {
    if (std::is_same<T, Song>::value) {
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            if (it->getTitle() == itemTitle) {
                songs.erase(it);
                std::cout << "Song '" << itemTitle << "' removed from the library." << std::endl;
                return;
            }
        }
        std::cout << "Song '" << itemTitle << "' not found in the library." << std::endl;
    } else if (std::is_same<T, Playlist>::value) {
        for (auto it = playlists.begin(); it != playlists.end(); ++it) {
            if (it->getTitle() == itemTitle) {
                playlists.erase(it);
                std::cout << "Playlist '" << itemTitle << "' removed from the library." << std::endl;
                return;
            }
        }
        std::cout << "Playlist '" << itemTitle << "' not found in the library." << std::endl;
    } else {
        std::cout << "Error: Invalid type." << std::endl;
    }
}

void MusicLibrary::print() {
    for (const auto& item : songs) {
        std::cout << item << std::endl;
    }
}

std::vector<Song> MusicLibrary::getSongVector() {
    return songs;
}

std::vector<Playlist> MusicLibrary::getPlaylistVector() {
    return playlists;
}

MusicLibrary::sortCriteria MusicLibrary::getSortCriteria() const {
    return criteria;
}

template<typename T>
bool MusicLibrary::isEmpty(std::vector<T> &vector) {
    if (vector.empty()) {
        return true;
    }
    return false;
}


//double MusicLibrary::calculateDurationPlaylist() {
//    double duration = 0;
//    for (const auto& item : songs) {
//        duration += item.getDuration();
//    }
//    return duration;
//}

template<typename T>
void MusicLibrary::sortItem(std::vector<T> &vector, sortCriteria sortCriteria) {
    switch(sortCriteria){
        case sortCriteria::DURATION:
            std::sort(vector.begin(), vector.end(), [](const T& a, const T& b) {
                return a.getDuration() < b.getDuration;
            });
            break;

        case sortCriteria::TITLE:
            std::sort(vector.begin(), vector.end(), [](const T& a, const T& b) {
                return a.getTitle() < b.getTitle();
            });
            break;
    }
}


