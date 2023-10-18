#pragma once

#include "FileManager.hpp"
#include <string>

class Player {
  public:
    Player();
    ~Player();

    void play(const std::string &filename);
    void pause();
    void stop();
};
