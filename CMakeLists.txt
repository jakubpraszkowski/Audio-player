cmake_minimum_required(VERSION 3.24)
project(MusicLibrary)
set(CMAKE_CXX_STANDARD 17)

#include_directories(
#        ~/Projekty/Biblioteki_zew/taglib/
#        ~/Projekty/Biblioteki_zew/taglib/taglib/
#        ~/Projekty/Biblioteki_zew/taglib/taglib/ape
#        ~/Projekty/Biblioteki_zew/taglib/taglib/asf
#        ~/Projekty/Biblioteki_zew/taglib/taglib/flac
#        ~/Projekty/Biblioteki_zew/taglib/taglib/it
#        ~/Projekty/Biblioteki_zew/taglib/taglib/mod
#        ~/Projekty/Biblioteki_zew/taglib/taglib/mp4
#        ~/Projekty/Biblioteki_zew/taglib/taglib/mpc
#        ~/Projekty/Biblioteki_zew/taglib/taglib/mpeg
#        ~/Projekty/Biblioteki_zew/taglib/taglib/ogg
#        ~/Projekty/Biblioteki_zew/taglib/taglib/riff
#        ~/Projekty/Biblioteki_zew/taglib/taglib/s3m
#        ~/Projekty/Biblioteki_zew/taglib/taglib/toolkit
#        ~/Projekty/Biblioteki_zew/taglib/taglib/trueaudio
#        ~/Projekty/Biblioteki_zew/taglib/taglib/wavpack
#        ~/Projekty/Biblioteki_zew/taglib/taglib/xm
#)

add_executable(MusicLibrary src/main.cpp src/Song.cpp include/Audio-player/Song.hpp src/MusicLibrary.cpp include/Audio-player/MusicLibrary.hpp src/UserInterface.cpp include/Audio-player/UserInterface.hpp src/AudioPlayer.cpp include/Audio-player/AudioPlayer.hpp src/Playlist.cpp include/Audio-player/Playlist.hpp src/Tag.cpp include/Audio-player/Tag.hpp include/Audio-player/Tag.hpp
        src/VorbisFormat.cpp
        include/Audio-player/VorbisFormat.hpp)
