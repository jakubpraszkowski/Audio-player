cmake_minimum_required(VERSION 3.24)
project(MusicLibrary)

set(CMAKE_CXX_STANDARD 17)

add_executable(MusicLibrary main.cpp Song.cpp Song.h MusicLibrary.cpp MusicLibrary.h UserInterface.cpp UserInterface.h AudioPlayer.cpp AudioPlayer.h Playlist.cpp Playlist.h)
