# Audio Player

The Music Library project is written in C++17 and allows users to manage their collection of songs and playlists.

# Features
* Adding Songs: Users can add new songs to the library by providing the title, artist, album, genre, release year, and duration of the song.

* Creating Playlists: Users can create playlists and add selected songs to them. They can also remove playlists when they are no longer needed.

* Removing Songs: If users want to remove certain songs from the library, they can do so using the appropriate option.

* Sorting Songs and Playlists: The program allows users to sort songs and playlists based on various criteria such as title, duration, artist, and genre. Users can choose their preferred sorting method, making it easy to organize their music.

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
