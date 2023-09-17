cmake_minimum_required(VERSION 3.24)
project(MusicLibrary)
set(CMAKE_CXX_STANDARD 17)

add_executable(MusicLibrary
        src/main.cpp src/Song.cpp include/Audio-player/Song.hpp src/MusicLibrary.cpp include/Audio-player/MusicLibrary.hpp src/UserInterface.cpp include/Audio-player/UserInterface.hpp src/AudioPlayer.cpp include/Audio-player/AudioPlayer.hpp src/Playlist.cpp include/Audio-player/Playlist.hpp src/Tag.cpp include/Audio-player/Tag.hpp include/Audio-player/Tag.hpp
        include/Audio-player/Album.hpp
        src/Album.cpp
        src/MusicItem.cpp
        include/Audio-player/MusicItem.hpp
        include/Audio-player/FileManager.hpp
        src/FileManager.cpp
)

find_package(SFML REQUIRED audio)
set(Taglib_DIR "/usr/local/bin/taglib-config.cmake")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(MusicLibrary PRIVATE sfml-system sfml-audio sfml-window sfml-graphics sfml-network tag ${CURSES_LIBRARY})
