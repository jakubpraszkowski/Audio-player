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

add_executable(MusicLibrary main.cpp Song.cpp Song.h MusicLibrary.cpp MusicLibrary.h UserInterface.cpp UserInterface.h AudioPlayer.cpp AudioPlayer.h Playlist.cpp Playlist.h Tag.cpp Tag.h Tag.h)
