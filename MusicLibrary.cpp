#include <algorithm>
#include "MusicLibrary.h"

template <typename T>
void MusicLibrary<T>::addSong(Song& song) {
    songs.push_back(song);
}

template <typename T>
void MusicLibrary<T>::addPlaylist(Playlist& playlist) {
    playlists.push_back(playlist);
}

template <typename T>
void MusicLibrary<T>::removeSong(Song& song) {
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].getTitle() == song.getTitle() && songs[i].getArtist() == song.getArtist()) {
            songs.erase(songs.begin() + i);
            break;
        }
    }
}

template <typename T>
void MusicLibrary<T>::removePlaylist(Playlist& playlist) {
    for (int i = 0; i < playlists.size(); i++) {
        if (playlists[i].getTitle() == playlist.getTitle()) {
            playlists.erase(playlists.begin() + i);
            break;
        }
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
