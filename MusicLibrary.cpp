#include <algorithm>
#include "MusicLibrary.h"

template <typename T>
void MusicLibrary<T>::addSong(const Song& song) {
    songs.push_back(song);
}

template <typename T>
void MusicLibrary<T>::addPlaylist(const Playlist& playlist) {
    playlists.push_back(playlist);
}

template <typename T>
void MusicLibrary<T>::removeItem(const std::string &itemTitle) {
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


template<typename T>
void MusicLibrary<T>::print() {
    for (const auto& item : songs) {
        std::cout << item << std::endl;
    }
}

template<typename T>
bool MusicLibrary<T>::compareByName(const T& t1, const T& t2) {
    return t1.getTitle() < t2.getTitle();
}

template<typename T>
bool MusicLibrary<T>::compareByCreator(const T& t1, const T& t2) {
    return t1.getArtist() < t2.getArtist();
}

template<typename T>
bool MusicLibrary<T>::compareByGenre(const Song& s1, const Song& s2) {
    return s1.getGenre() < s2.getGenre();
}

template<typename T>
bool MusicLibrary<T>::compareByDuration(const T& t1, const T& t2) {
    return t1.getDuration() < t2.getDuration();
}

template<typename T>
bool MusicLibrary<T>::compareByYear(const T& t1, const T& t2) {
    return t1.getYear() < t2.getYear();
}

template<typename T>
bool MusicLibrary<T>::compareByAlbum(const Song& s1, const Song& s2) {
    return s1.getAlbum() < s2.getAlbum();
}

template<typename T>
void MusicLibrary<T>::sortByCreator() {
    std::sort(songs.begin(), songs.end(), &MusicLibrary::compareByCreator);
}

template<typename T>
void MusicLibrary<T>::sortByName(){
    std::sort(songs.begin(), songs.end(), &MusicLibrary::compareByName);
}

template<typename T>
void MusicLibrary<T>::sortByGenre() {
    std::sort(songs.begin(), songs.end(), &MusicLibrary::compareByGenre);
}

template<typename T>
void MusicLibrary<T>::sortByYear() {
    std::sort(songs.begin(), songs.end(), &MusicLibrary::compareByYear);
}

template<typename T>
void MusicLibrary<T>::sortByDuration() {
    std::sort(songs.begin(), songs.end(), &MusicLibrary::compareByDuration);
}

template<typename T>
void MusicLibrary<T>::sortByAlbum() {
    std::sort(songs.begin(), songs.end(), &MusicLibrary::compareByAlbum);
}

template<typename T>
bool MusicLibrary<T>::isEmpty(std::vector<T> &vector) {
    if (vector.empty()) {
        return true;
    }
    return false;
}

template<typename T>
double MusicLibrary<T>::calculateDurationPlaylist() {
    double duration = 0;
    for (const auto& item : songs) {
        duration += item.getDuration();
    }
    return duration;
}

template class MusicLibrary<Song>;
template class MusicLibrary<Playlist>;
