# TerminalTunes

This C++ project utilizes system audio capabilities to play various audio formats, offering a simple yet efficient way to groove to your music collection without leaving your terminal session.

# Features
* Adding Songs: Users can add new songs to the library by providing the title, artist, album, genre, release year, and duration of the song.

* Creating Playlists: Users can create playlists and add selected songs to them. They can also remove playlists when they are no longer needed.

* Removing Songs: If users want to remove certain songs from the library, they can do so using the appropriate option.

* Sorting Songs and Playlists: The program allows users to sort songs and playlists based on various criteria such as title, duration, artist, and genre. Users can choose their preferred sorting method, making it easy to organize their music.

# Dependencies

Project depends on external libraries that I recomend installing using your package manager. Due to a bug with current version of Taglib in Fedora 38 repository it's not possible to link it with find_package() in CMake. The easiest way is look for the binaries yourself and hardcode it.
* taglib & taglib-devel
* ncurses & ncurses-devel
* SFML & SFML-devel

# Implementation

The project is implemented using classes like "Song," "Playlist," and "MusicLibrary," which are responsible for storing and managing data about songs and playlists. The program utilizes smart pointers like std::shared_ptr for memory management of songs, ensuring safe and efficient handling of objects.

# Requirements

To compile and run the Music Library project, you need:

* C++17 compatible compiler
* CMake (for building the project)

Getting Started

* Clone this repository to your local machine.
* Build the project using CMake.
* Run the executable to launch the Music Library application.
