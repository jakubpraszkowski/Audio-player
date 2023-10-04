#include <algorithm>
#include "../include/Audio-player/MusicLibrary.hpp"

MusicLibrary::MusicLibrary(fs::path _directory)
{
    this->directory = "/home/${USER}/Music";
}

void MusicLibrary::addSong(const Song &song)
{
    songs.push_back(song);
}

void MusicLibrary::addPlaylist(const Playlist &playlist)
{
    playlists.push_back(playlist);
}

// template <typename T>
// void MusicLibrary::removeItem(const std::string &itemTitle) {
//     if (std::is_same<T, Song>::value) {
//         for (auto it = songs.begin(); it != songs.end(); ++it) {
//             if (it->getTitle() == itemTitle) {
//                 songs.erase(it);
//                 std::cout << "Song '" << itemTitle << "' removed from the library." << std::endl;
//                 return;
//             }
//         }
//         std::cout << "Song '" << itemTitle << "' not found in the library." << std::endl;
//     } else if (std::is_same<T, Playlist>::value) {
//         for (auto it = playlists.begin(); it != playlists.end(); ++it) {
//             if (it->getTitle() == itemTitle) {
//                 playlists.erase(it);
//                 std::cout << "Playlist '" << itemTitle << "' removed from the library." << std::endl;
//                 return;
//             }
//         }
//         std::cout << "Playlist '" << itemTitle << "' not found in the library." << std::endl;
//     } else {
//         std::cout << "Error: Invalid type." << std::endl;
//     }
// }

template <typename T>
void MusicLibrary::printVector(const std::vector<T> &vec)
{
    for (const auto &item : *vec)
    {
        std::cout << item << std::endl;
    }
}

template <typename T>
std::vector<T> &MusicLibrary::getVector()
{
    if constexpr (std::is_same_v<T, Playlist>)
    {
        return playlists;
    }
    else if constexpr (std::is_same_v<T, Song>)
    {
        return songs;
    }
    else if constexpr (std::is_same_v<T, Album>)
    {
        return albums;
    }
    else
    {
        throw std::runtime_error("Unsupported vector type");
    }
}

template <typename T>
bool MusicLibrary::isEmpty(std::vector<T> &vector)
{
    if (vector.empty())
    {
        return true;
    }
    return false;
}

void MusicLibrary::updateSongs(FileManager &fm)
{
    std::regex pattern(".*/([^/]+)\\.ogg");
    for (const auto &path : fm.getOggFilePaths())
    {
        TagLib::FileRef f(path.c_str());
        if (!f.isNull() && f.tag())
        {
            TagLib::Tag *tag = f.tag();
            // std::cout << "title:" << tag->title() << std::endl;
            // std::cout << "artist:" << tag->artist() << std::endl;
            // std::cout << "album:" << tag->album() << std::endl;
            // std::cout << "genre:" << tag->genre() << std::endl;
            // std::cout << "year:" << tag->year() << std::endl;
            // std::cout << "duration:" << f.audioProperties()->lengthInSeconds() << std::endl;
            // std::cout << "path:" << path << std::endl;
            // std::cout << "---------------------" << std::endl;
            std::smatch matches;
            if (!(std::regex_search(path, matches, pattern) && matches.size() == 2))
            {
                std::cout << "Regex: No match found." << std::endl;
            }

            std::string title = matches[1].str();
            int duration = f.audioProperties()->lengthInSeconds();

            Song song(title, duration);
            // Song song(title, artist, album, genre, year, duration);
            songs.push_back(song);
        }
    }
}

Song &MusicLibrary::getSong(const std::string &songTitle)
{
    for (auto &song : songs)
    {
        if (song.getTitle() == songTitle)
        {
            return song;
        }
    }
    throw std::runtime_error("Song not found");
}

void MusicLibrary::printSongs()
{
    std::cout << "dupa" << std::endl;
    for (const auto &song : songs)
    {

        std::cout << song.getTitle() << std::endl;
    }
}