cmake_minimum_required(VERSION 3.24)
project(MusicLibrary VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

include(UpdateSubmodules.cmake)

include(CTest)

add_subdirectory(external)

file(GLOB SRC_FILES "src/*.cpp")
add_library(MusicLibraryLib ${SRC_FILES})
add_executable(MusicLibrary src/main.cpp)

enable_testing()

file(GLOB TEST_FILES_ENTITY "tests/entity_tests/*.cpp")
add_executable(entity_tests ${TEST_FILES_ENTITY})

file(GLOB TEST_FILES_FUNCTIONALITY "tests/functionality_tests/*.cpp")
add_executable(functionality_tests ${TEST_FILES_ENTITY})

find_package(SFML REQUIRED audio)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(entity_tests gtest gtest_main pthread sfml-system sfml-audio sfml-window sfml-graphics sfml-network tag z ${CURSES_LIBRARY} MusicLibraryLib)
target_link_libraries(functionality_tests gtest gtest_main pthread sfml-system sfml-audio sfml-window sfml-graphics sfml-network tag z ${CURSES_LIBRARY} MusicLibraryLib)

target_link_libraries(MusicLibrary PRIVATE sfml-system sfml-audio sfml-window sfml-graphics sfml-network tag z ${CURSES_LIBRARY} MusicLibraryLib)

add_test(NAME CheckEntites COMMAND entity_tests)
add_test(NAME CheckFunctionality COMMAND functionality_tests)
