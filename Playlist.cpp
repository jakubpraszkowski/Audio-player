#include "Playlist.h"

//std::string Playlist::getName() const {
//    return name;
//}
//
//void Playlist::setName(const std::string &name) {
//    Playlist::name = name;
//}
//
//Playlist::Playlist(std::string name) {
//    this->name = name;
//}

//std::string Playlist::getArtist() const {
//    return artist;
//}
//
//void Playlist::setArtist(const std::string &artist) {
//    Playlist::artist = artist;
//}
//
//void Playlist::setDuration(int duration) {
//    Playlist::duration = duration;
//}
//
//int Playlist::getDuration() const {
//    return duration;
//}
Playlist::Playlist(std::string title) {
    this->title = title;
}

void Playlist::createPlaylist() {
    std::cout << "Enter the title of the playlist: ";
    std::cin >> title;
}
